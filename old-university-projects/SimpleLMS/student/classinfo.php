<?php include '../core/init.php';?>
<?php protect_page(); ?>
<?php include '../includes/overall/header.php';?>

<h1>
<?php
$classid = $_GET['id'];
$classname = mysql_result(mysql_query("SELECT `name` FROM `classes` WHERE `id` = '$classid'"), 0, 'name');
echo $classname, ' Information';
?>
</h1>

<p>
<?php
$classinfo = mysql_result(mysql_query("SELECT `info` FROM `classes` WHERE `id` = '$classid'"), 0, 'info');
echo $classinfo;
?>
</p>

<?php include '../includes/overall/footer.php';?>