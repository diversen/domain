<?php

/**
 * install file for 
 * we add the following package doc code if we want good docs
 *
 * @package     system
 */


/**
 * We set a version, so we can control if there are any upgrades etc.
 */
$_INSTALL['VERSION'] = 1.511;


/**
 * We also create a menu item to be added to the main menu placed in database
 */

/**
 * We also create a menu item to be added to the main menu
 */
$_INSTALL['MAIN_MENU_ITEMS'] = array ();
$_INSTALL['MAIN_MENU_ITEMS'][] = array (
    'title' => 'domain', // Title of the menu item
    'url' => '/domain/index', // url of the item
    'module_name' => 'domain', // beloning to which module
    'parent' => 0, // does it have a parent item
    'weight' => 0, // weight
    'auth' => config::getModuleIni('domain_allow'), // Who can se this menu item
    'admin_only' => true,
    'section' => 'system'
);

$_INSTALL['IS_SHELL'] = "1";

$_INSTALL['PUBLIC_CLONE_URL'] = 'git://github.com/diversen/domain.git';
$_INSTALL['PRIVATE_CLONE_URL'] = 'git@github.com:diversen/domain.git';
