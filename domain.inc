<?php

// shell part of the domain module

include_module ('domain');
function domain_update_db () {
    $d = new domain ();
    $rows = $d->getAll();
    $str = '';
    foreach ($rows as $row) {
        $str.= $row['host'] . "\n";
    } 
    print $str;
}

mainCli::setCommand('domain', array(
    'description' => "Command for adding file from domain table to apache config file ",
));

mainCli::setOption('domain_update_db', array(
    'long_name'   => '--up',
    'description' => 'Will update apache configuration with domains from db table',
    'action'      => 'StoreTrue'
));
