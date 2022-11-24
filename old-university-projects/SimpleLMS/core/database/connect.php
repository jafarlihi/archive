<?php
error_reporting(E_ALL ^ E_DEPRECATED);
mysql_connect('address_hostname', 'mysql_username', 'mysql_password');
mysql_select_db('mysql_db_name');
?>