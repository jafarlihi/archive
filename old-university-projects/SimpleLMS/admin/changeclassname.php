<?php include '../core/init.php';?>
<?php 
protect_page();
protect_page_teacher();
?>
<?php include '../includes/overall/header.php';?>

<?php
$classid = $_GET['id'];
$classname = mysql_result(mysql_query("SELECT `name` FROM `classes` WHERE `id` = '$classid'"), 0, 'name');
echo '<h1>Changing the name of class: ', $classname, '</h1>';
?>

<form action="" method="post">
	<ul>
		<li>New class name:<br>
		<input type="text" name="newname">
		</li>
		<li>
		<input type="submit" value="Change Class Name">
		</li>
	</ul>
</form>

<?php
	if (empty($_POST) === false){
	$newname = $_POST['newname'];
	mysql_query("UPDATE `classes` SET name='$newname' WHERE `id` = '$classid';");
	echo 'Updated name of class ', $classname, ' to ', $newname, ' successfully.';
	}
?>

<?php include '../includes/overall/footer.php';?>