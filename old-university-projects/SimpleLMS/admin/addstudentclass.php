<?php include '../core/init.php';?>
<?php 
protect_page();
protect_page_teacher();
?>
<?php include '../includes/overall/header.php';?>

<?php
$classid = $_GET['id'];
$classname = mysql_result(mysql_query("SELECT `name` FROM `classes` WHERE `id` = '$classid'"), 0, 'name');
echo '<h1>Add student to the class named ', $classname, '</h1>';
?>

<form action="" method="post">
	<ul>
		<li>Student's username:<br>
		<input type="text" name="username">
		</li>
		<li>
		<input type="submit" value="Add Student">
		</li>
	</ul>
</form>

<?php
	if (empty($_POST) === false){
	$username = $_POST['username'];
	$studentid = mysql_result(mysql_query("SELECT `id` FROM `logins` WHERE '$username' = `username`"), 0, 'id');
	mysql_query("INSERT INTO `participation` (classid, studentid) VALUES ($classid, $studentid);");
	echo 'Student with username of ', $username, ' was successfully added to class named ', $classname, '.';
	}
?>

<?php include '../includes/overall/footer.php';?>