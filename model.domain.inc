<?php

include_once "coslib/form_helpers.php";

class domain {
    
    /**
     * var holding errors
     * @var type $errors
     */
    public $errors = array ();
    
    /**
     * var holding db object
     * @var object $db
     */
    public $db = null;
    function __construct() {
        
        // we will need to connect to top level config/config.ini -we only want
        // all domains in one database table
        
        $file = _COS_PATH . "/config/config.ini";
        $config = config::getIniFileArray($file, true);

        //print_r( $config);
        $this->db = new db();
        $this->db->connect();
    }
    
    public function getAll () {
        return $this->db->selectAll('domain', 'host');
        //echo config::getMainIni('url');
        //$rows = dbQ::setSelect('domain')->fetch();
        //print_r($rows);
        //die;
    }
    
    public function displayDeleteForm ($row) {
        echo lang::translate('domain_delete_info', array ($row['host']));
        echo formHelpers::confirmDeleteForm('submit_delete', 
                lang::translate('domain_confirm_delete_legend'));

    }
    /**
     * displays base info 
     * To create or not
     */
    public function displayBaseInfo () {

        
        $master = config::getMainIni('master');
        if (!$master) {
            echo lang::translate('domain_can_not_add_domain_to_non_master');
            return;
        }
        
        $row = $this->getRowFromServername ();
        
        if (!empty($row)) {
            //headline_message(lang::translate('domain_delete_domain'));
            echo lang::translate('domain_info_allow_create_ip');
            echo "<br />";
            echo $_SERVER['SERVER_ADDR'];
            echo "<br />\n";
            $this->displayDeleteForm($row);
            return false;
        }
        
        $server_name = config::getMainIni('server_name');
        if (empty($row)) {
            headline_message(lang::translate('domain_add_domain'));
            echo lang::translate('domain_info_allow_create', array ($server_name));
            echo "<br />";
            echo lang::translate('domain_info_allow_create_ip');
            echo "<br />";
            echo $_SERVER['SERVER_ADDR'];
            return true;
        } else {
            $this->errors[] = lang::translate('domain_info_deny_create');
            echo lang::translate('domain_info_deny_create');
            return false;
        }
    }
    
    function getRowFromServerName () {
        $server_name = config::getMainIni('server_name');
        $row = $this->db->selectOne('domain', 'master', $server_name);
        return $row;
    }
    
    function delete () {
        $row = $this->getRowFromServerName();
        if (empty($row['host'])) {
            cos_error_log('Should not happen');
            return;
        }
        
        $path = _COS_PATH . "/config/multi/$row[host]";
        rrmdir($path);
        return $this->db->delete('domain', 'host', $row['host']);
    }

    /**
     * validates a new hostname. 
     * @param string $host the hostname to add 
     */
    function validateHostname ($host) {
        
        $ary = explode(".", $host);
        if (count($ary) < 2) {
            $this->errors[] = lang::translate('domain_error_not_valid_name');
            return;
        }
        
        // validate parts
        foreach ($ary as $subject) {
            if (!preg_match(('/^([a-zA-Z0-9-]+)$/'), $subject)) {
                $this->errors[] = lang::translate('domain_error_not_valid_name');
                return;
            }
        }

        $server_name = config::getMainIni('server_name');
        $master_config = _COS_PATH . "/config/multi/$server_name/config.ini";
        if (!file_exists($master_config)) {
            $this->errors[] = lang::translate('domain_error_no_master_config') . ' ' .   
                    $server_name;
            return;
        }
        
        $config_file = _COS_PATH . "/config/multi/$host/config.ini";
        if (file_exists($config_file)) {
            $this->errors[] = lang::translate('domain_hostname_exists');
            return;
        }
    }
    
    /**
     * 
     * @param string $host the name of the host to add.  
     * @return boolean $res true on success and false on failure
     */
    function addHostDb ($host) {
        $values = array (
            'master' => config::getMainIni('server_name'),
            'host' => $host,
            'user_id' => session::getUserId()
        );
        
        $res = $this->db->insert('domain', $values);
        return $res;
    }
    
    /**
     * adds a new domain
     * @return boolean $res true on success and false on failure
     */
    function add() {
        $domain = $_POST['domain'];
        
        // read master configuration - only change is server_name
        $master = config::getMainIni('server_name');
        $file = _COS_PATH . "/config/multi/$master/config.ini";
        $master_conf = config::getIniFileArray($file, true);
        $master_conf['server_name'] = $domain;
        $master_conf['server_name_master'] = $master;
        $master_conf['server_redirect'] = $domain;
        $master_conf['master'] = 0;
        $master_conf['robots'] = 'index, follow';
        // ini array to string
        $str = config::arrayToIniFile($master_conf);
        
        $path_name = _COS_PATH . "/config/multi/$domain"; 
        $res = @mkdir($path_name);
        if (!$res) return false;
        $site_ini = "$path_name/config.ini";
        $res = file_put_contents($site_ini, $str);
        if (!$res) return false;
        return $this->addHostDb($domain);
    }
    
    /**
     * diaplys domain form
     */
    function form () {
        $_POST = html::specialEncode($_POST);
        $form = new htmL();
        $form->init(null, 'submit');
        $form->formStart('domain_form');
        $form->legend(lang::translate('domain_add_domain'));
        //$form->label('domain', lang::translate('domain_add_domain'));
        $form->text('domain');
        $form->submit('submit', lang::system('submit'));
        $form->formEnd();
        echo $form->getStr();
    }
    
    /**
     * destruct by reeastablish default db connection
     */
    public function __destruct()
    {
        $db = new db();
        $db->connect();
    }
}
