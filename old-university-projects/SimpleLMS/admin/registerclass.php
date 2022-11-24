<?php include '../core/init.php';?>
<?php 
protect_page(); 
protect_page_admin();
?>
<?php include '../includes/overall/header.php';?>

<script type="text/javascript" src="../assets/editor/nicEdit.js"></script>
<script type="text/javascript">
bkLib.onDomLoaded(function() {
	new nicEditor({iconsPath : '../assets/editor/nicEditorIcons.gif'}).panelInstance('textid');
});
</script>

<?php
if (empty($_POST) === false){
	foreach($_POST as $key=>$value){
		if(empty($value) and empty($errors)){
			$errors[] = 'Please fill in all of the fields.';
                        break 1;
		}
	}

if (empty($errors) === true){
	if (user_exists($_POST['teacherusername']) === false){
		$errors[] = 'Username \'' . $_POST['teacherusername'] . '\' is not registered.';
	}
}
}
?>

<h1>Register a new class:</h1>
<?php
if (isset($_GET['success']) && empty($_GET['success'])){
	echo 'Registration is successful.';
} else {
if (empty($_POST) === false && empty($errors) === true){
	$info = sanitize($_POST['info']);
	$name = sanitize($_POST['name']);
        $teacherusername = sanitize($_POST['teacherusername']);
	$teacherid = id_from_username($teacherusername);
	mysql_query("INSERT INTO `classes` (info, name, teacherid) VALUES ('$info', '$name', '$teacherid')");
	header('Location: registerclass.php?success');
        //echo($teacherid);
	exit();
} else if (empty($errors) === false) {
	echo output_errors($errors);
}
?>

<form action="" method="post" id="register_class">
	<ul>
		<li>Class name:<br>
		<input type="text" name="name">
		</li>
		<li>Instructor's username:<br>
		<input type="text" name="teacherusername">
		</li>
		</form>
		<br>
		<li>Class info:<br>
		<textarea name="info" form="register_class" rows="8" cols="75" id="textid">Enter class info here.</textarea>
		</li>
		<li>
		<input type="submit" value="Register Class" form="register_class">
		</li>
	</ul>

<?php 
}
include '../includes/overall/footer.php';
?>