<?php include '../core/init.php';?>
<?php 
protect_page();
protect_page_admin();
?>
<?php include '../includes/overall/header.php';?>

<?php
$teacherid = $_GET['id'];
$teacherusername = mysql_result(mysql_query("SELECT `username` FROM `logins` WHERE `id` = '$teacherid'"), 0, 'username');
echo '<h1>Change username of account: ', $teacherusername, '</h1>';
?>

<form action="" method="post">
	<ul>
		<li>New username:<br>
		<input type="text" name="newname">
		</li>
		<li>
		<input type="submit" value="Change Username">
		</li>
	</ul>
</form>

<?php
	if (empty($_POST) === false){
	$newname = $_POST['newname'];
	mysql_query("UPDATE `logins` SET username='$newname' WHERE `id` = '$teacherid';");
        echo 'Username was changed successfully.';
	}
?>

<?php include '../includes/overall/footer.php';?>