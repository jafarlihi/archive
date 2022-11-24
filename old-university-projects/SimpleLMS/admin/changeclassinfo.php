<?php include '../core/init.php';?>
<?php 
protect_page();
protect_page_teacher();
?>
<?php include '../includes/overall/header.php';?>

<script type="text/javascript" src="../assets/editor/nicEdit.js"></script>
<script type="text/javascript">
bkLib.onDomLoaded(function() {
	new nicEditor({iconsPath : '../assets/editor/nicEditorIcons.gif'}).panelInstance('newinfo');
});
</script>

<?php
$classid = $_GET['id'];
$classname = mysql_result(mysql_query("SELECT `name` FROM `classes` WHERE `id` = '$classid'"), 0, 'name');
echo '<h1>Change description of class named ', $classname, '</h1>';
?>

<form action="" method="post" id="change_info">
	<ul>
</form>
		<li>Class info:<br>
		<textarea name="newinfo" form="change_info" rows="8" cols="75" id="newinfo">
		<?php
		$currentinfo = mysql_result(mysql_query("SELECT `info` FROM `classes` WHERE `id` = '$classid'"), 0, 'info');
		echo $currentinfo;
		?>
		</textarea>
		</li>
		<li>
		<input type="submit" value="Change Class Info" form="change_info">
		</li>
	</ul>

<?php
	if (empty($_POST) === false){
	$newinfo = $_POST['newinfo'];
        $newinfo = sanitize($newinfo);
	mysql_query("UPDATE `classes` SET info='$newinfo' WHERE `id` = '$classid';");
	echo 'Updated description of class named ', $classname, ' successfully.';
	}
?>

<?php include '../includes/overall/footer.php';?>