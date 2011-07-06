<?php
//Session autostart?
$conn = ''; //connection

$uid = ''; //user id


function ajax_inject_drupal_connection() {
	static $conn;
	$db_user = '';
	$db_pass = '';
	$db_host = '';

}

function ajax_inject_drupal_user() {
	if(isset($_COOKIE[session_name()])){
	}
}

function ajax_inject_init() {

}
