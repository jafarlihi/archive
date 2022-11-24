<?php include '../core/init.php';?>
<?php 
protect_page();
protect_page_teacher();
?>
<?php include '../includes/overall/header.php';?>

<?php
$username = $_SESSION['editgrade_username'];
$classid = $_SESSION['editgrade_classid'];
?>

<script type="text/javascript" src="../assets/editor/nicEdit.js"></script>
<script type="text/javascript">
bkLib.onDomLoaded(function() {
	new nicEditor({iconsPath : '../assets/editor/nicEditorIcons.gif'}).panelInstance('newinfo');
});
</script>

<?php
$studentid = mysql_result(mysql_query("SELECT `id` FROM `logins` WHERE `username` = '$username'"), 0, 'id');
$classname = mysql_result(mysql_query("SELECT `name` FROM `classes` WHERE `id` = '$classid'"), 0, 'name');
echo '<h1>Change ', $classname, ' grades of student with username of ', $username, '</h1>';
?>

<form action="" method="post" id="formname">
	<ul>
</form>
		<li>Grades:<br>
		<textarea name="newinfo" form="formname" rows="20" cols="28" id="newinfo">
		<?php
		$currentgrades = mysql_result(mysql_query("SELECT `grades` FROM `participation` WHERE `classid` = '$classid' AND `studentid` = '$studentid'"), 0, 'grades');
		echo $currentgrades;
		?>
		</textarea>
		</li>
		<li>
		<input type="submit" value="Submit" form="formname">
		</li>
	</ul>

<?php
	if (empty($_POST) === false){
	$newinfo = $_POST['newinfo'];
	mysql_query("UPDATE `participation` SET grades='$newinfo' WHERE `studentid` = '$studentid' AND `classid` = '$classid';");
	echo 'Updated grades successfully.';
	}
?>

<?php include '../includes/overall/footer.php';?>