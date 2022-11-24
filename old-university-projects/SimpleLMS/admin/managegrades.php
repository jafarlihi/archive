<?php include '../core/init.php';?>
<?php 
protect_page();
protect_page_teacher();
?>
<?php include '../includes/overall/header.php';?>

<?php
$classid = $_GET['id'];
$classname = mysql_result(mysql_query("SELECT `name` FROM `classes` WHERE `id` = '$classid'"), 0, 'name');
echo '<h1>Manage grades for class named ', $classname, '</h1>';
?>

Choose a student:
<form action="" method="post">
<select name="students_username" style="min-width: 150px;">
<option disabled="disabled">Pick a student</option>
<?php
	$result = mysql_query("SELECT COUNT(1) FROM `participation` WHERE `classid` = '$classid'");
	$num_rows = mysql_result($result, 0, 0);
	$i = 0;
	$students = array();
	while ($i < $num_rows){
	$students_id[$i] = mysql_result(mysql_query("SELECT `studentid` FROM `participation` WHERE `classid` = '$classid'"), $i, 'studentid');
	$students_username[$i] = mysql_result(mysql_query("SELECT `username` FROM `logins` WHERE `id` = '$students_id[$i]'"), 0, 'username');
	$i++;
	}
	while ($i > 0){
        echo "<option value='".$students_username[$i-1]."'>".$students_username[$i-1]."</option>";
	$i--;
	}
?>
<input type="submit" value="Edit">
</select>
</form>
</p>

<?php
if (empty($_POST) === false){
$_SESSION['editgrade_username'] = $_POST['students_username'];
$_SESSION['editgrade_classid'] = $classid;
header('Location: editgrade.php');
}
?>

<?php include '../includes/overall/footer.php';?>