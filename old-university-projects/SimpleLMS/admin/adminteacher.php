<?php include '../core/init.php'; ?>
<?php 
protect_page(); 
protect_page_admin();
?>
<?php include '../includes/overall/header.php'; ?>

<h1>Manage Instructors</h1>
<br>
<a class="myButton" href="registerteacher.php">Register a New Instructor</a><br><br>
<br>
<br>
Edit an existing instructor account:&nbsp;
<form action="" method="post" style="display:inline;">
<select name="teacher" style="min-width: 150px;">
<option disabled="disabled">Pick an instructor</option>
<?php
	$result = mysql_query("SELECT COUNT(1) FROM `logins` WHERE `access` = 1");
	$num_rows = mysql_result($result, 0, 0);
	$i = 0;
	$teachers = array();
	while ($i < $num_rows){
	$teachers[$i] = mysql_result(mysql_query("SELECT `username` FROM `logins` WHERE `access` = 1"), $i, 'username');
	$i++;
	}
	while ($i > 0){
        echo "<option value='".$teachers[$i-1]."'>".$teachers[$i-1]."</option>";
	$i--;
	}
?>
<input type="submit" value="Edit">
</select>
</form>

<?php
if (empty($_POST) === false){
$_SESSION['editteacher_username'] = $_POST['teacher'];
header('Location: admineditteacher.php');
}
?>

<?php include '../includes/overall/footer.php';?>