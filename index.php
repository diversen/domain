<?php

if (!session::checkAccessControl('domain_allow')){
    return;
}

$d = new domain();
$res = $d->displayBaseInfo();

if (isset($_POST['submit_delete'])) {
    $res = $d->delete();
    if ($res) {
        session::setActionMessage(lang::translate('domain_deleted_action_message'));
        http::locationHeader('/domain/index');
    } else {
        log::error('Error: Creating domain name');
    }
}

if (!$res) {
    return;
}



if (isset($_POST['submit'])) {
    $d->validateHostname($_POST['domain']);
    if (empty($d->errors)) {
        $res = $d->add();
        if ($res) {
            session::setActionMessage(lang::translate('domain_added'));
            http::locationHeader('/domain/index');
        } else {
            log::error('Error: Creating domain name');
        }
    } else {
        html::errors($d->errors);
    }
}

$d->form();


