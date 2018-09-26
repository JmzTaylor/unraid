<?php
/**
 * Copyright (C) 2018 Ethan P. (eth-p)
 */

$PLUGIN     = explode('/', $_SERVER['PHP_SELF'])[2];
$STYLESHEET = '/boot/config/plugins/' . $PLUGIN . '/custom.css';

header('Content-Type: text/css');

if (file_exists($STYLESHEET)) {
	$fh = fopen($STYLESHEET, 'r');
	fpassthru($fh);
	fclose($fh);
}

