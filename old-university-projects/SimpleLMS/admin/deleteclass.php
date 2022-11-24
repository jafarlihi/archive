<?php include '../core/init.php';?>
<?php 
protect_page();
protect_page_admin();
?>
<?php include '../includes/overall/header.php';?>

<?php
$classid = $_GET['id'];
$classname = mysql_result(mysql_query("SELECT `name` FROM `classes` WHERE `id` = '$classid'"), 0, 'name');
mysql_query("DELETE FROM `classes` WHERE `id` = '$classid'");
echo 'Class named ', $classname, ' was successfully deleted. You will be redirected to home page in 3 seconds.';
?>

<?php header("refresh:3;url=../index.php");?>

<?php include '../includes/overall/footer.php';?>