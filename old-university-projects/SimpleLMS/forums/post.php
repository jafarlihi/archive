<?php include '../core/init.php';?>
<?php protect_page();?>
<?php include '../includes/overall/header.php';?>

<script type="text/javascript" src="../assets/editor/nicEdit.js"></script>
<script type="text/javascript">
bkLib.onDomLoaded(function() {
    new nicEditor({iconsPath : '../assets/editor/nicEditorIcons.gif'}).panelInstance('content');
});
</script>

<?php
$classid = $_GET['id'];
$classid = sanitize($classid);
$classname = mysql_result(mysql_query("SELECT `name` FROM `classes` WHERE `id` = '$classid'"), 0, 'name');

sprintf('<h1>Posting in the Message Board of a class: %s</h1>', $classname);
?>

<form action="" method="post" id="make_post">
    <ul>
</form>
        <li>Write your post:<br>
        <textarea name="content" form="make_post" rows="16" cols="75" id="content">
        </textarea>
        </li>
        <li>
        <input type="submit" value="Post" form="make_post">
        </li>
    </ul>

<?php
if (empty($_POST) === false) {
    $content = $_POST['content'];
    $content = sanitize($content);
    $userid = $_SESSION['id'];
    $date = date('Y-m-d H:i:s');

    mysql_query(sprintf(
        "INSERT INTO forums (classid, userid, content, date) VALUES ('%s', '%s', '%s', '%s')",
        $classid,
        $userid,
        $content,
        $date
    ));

    sprintf(
        'You have successfully posted a message to the Message Board of the class %s
        <br><br>
        <a href=board.php?id=%s>Click to go back to the Message Board</a>',
        $classname,
        $classid
    );
}
?>

<?php include '../includes/overall/footer.php';?>
