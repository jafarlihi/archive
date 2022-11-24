<?php include '../core/init.php';?>
<?php 
protect_page();
protect_page_admin();
?>
<?php include '../includes/overall/header.php';?>

<?php
$classid = $_GET['id'];
$classname = mysql_result(mysql_query("SELECT `name` FROM `classes` WHERE `id` = '$classid'"), 0, 'name');
$currentteacherid = mysql_result(mysql_query("SELECT `teacherid` FROM `classes` WHERE `id` = '$classid'"), 0, 'teacherid');
$currentteachername = mysql_result(mysql_query("SELECT `username` FROM `logins` WHERE `id` = '$currentteacherid'"), 0, 'username');
echo '<h1>Change instructor of the class named ', $classname, '. Username of current class instructor: ', $currentteachername, '</h1>';
?>

<form action="" method="post">
	<ul>
		<li>Username of the new instructor:<br>
		<input type="text" name="username">
		</li>
                <br>
		<li>
		<input type="submit" value="Change Instructor">
		</li>
	</ul>
</form>

<?php
	if (empty($_POST) === false){
	$username = $_POST['username'];
	$teacherid = mysql_result(mysql_query("SELECT `id` FROM `logins` WHERE '$username' = `username`"), 0, 'id');
	mysql_query("UPDATE `classes` SET teacherid='$teacherid' WHERE `name` = '$classname'; ");
	echo 'Instructor with username ', $username, ' was successfully given control of class named ', $classname, '.';
	}
?>

<?php include '../includes/overall/footer.php';?>