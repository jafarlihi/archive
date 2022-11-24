<?php include '../core/init.php';?>
<?php protect_page();?>
<?php include '../includes/overall/header.php';?>

<h1>
<?php
$classid = $_GET['id'];
$classname = mysql_result(mysql_query("SELECT `name` FROM `classes` WHERE `id` = '$classid'"), 0, 'name');
echo 'Your ', $classname, ' Grades:';
?>
</h1>

<p>
<?php
$studentid = $_SESSION['id'];
$grades = mysql_result(mysql_query("SELECT `grades` FROM `participation` WHERE `classid` = '$classid' AND `studentid` = '$studentid'"), 0, 'grades');
echo $grades;

if (empty($grades) == true) {
    echo 'No grades are entered by the instructor.';
}
?>
</p>

<?php include '../includes/overall/footer.php';?>
