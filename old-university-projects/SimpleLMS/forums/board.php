<?php include '../core/init.php';?>
<?php protect_page();?>
<?php include '../includes/overall/header.php';?>

<?php
$classid = $_GET['id'];
$classid = sanitize($classid);
$classname = mysql_result(mysql_query("SELECT `name` FROM `classes` WHERE `id` = '$classid'"), 0, 'name');
echo '<h1>Viewing the Message Board of a class: ', $classname, '</h1>';
?>

<?php
$posts = array();
$i = 0;
$result = mysql_query("SELECT COUNT(*) FROM `forums` WHERE `classid` = '$classid'");
$num_rows = mysql_result($result, 0, 0);
while ($i < $num_rows) {
    $posts[$i] = mysql_result(mysql_query("SELECT `id` FROM `forums` WHERE `classid` = '$classid' ORDER BY `id` DESC"), $i, 'id');
    $i++;
}
?>

<ul>
<a class="myButton" style="display: inline-block; width: 103px;" href="post.php?id=<?php echo "$classid";?>" >Make a New Post</a><br><br><br>

<?php
if (empty($posts) === true) {
    echo "No posts have been made in the Message Board of this class.";
}
?>

<?php
$can_edit = 0;
$user_id = $_SESSION['id'];
$user_access = mysql_result(mysql_query("SELECT `access` FROM `logins` WHERE `id` = '$user_id'"), 0, 'access');
if ($user_access === '2' || $user_access === '1') {
    $can_edit = '1';
}
?>

<?php
foreach ($posts as $id) {
?>
<br>
<div class="post">
<?php
if ($id !== $delete_id) {
    $userid = mysql_result(mysql_query("SELECT `userid` FROM `forums` WHERE `id` = '$id'"), 0, 'userid');
    $username = username_from_id($userid);
    echo ('<post_author_text>Author: '.$username.'</post_author_text><br>');
    $date = mysql_result(mysql_query("SELECT `date` FROM `forums` WHERE `id` = '$id'"), 0, 'date');
    echo ('<post_date_text>'.$date.'</post_date_text>');

    if ($can_edit === '1') {
        echo(
        '
        <form method="POST" action="" style="display:inline; margin:0; padding:0;">
        <input type="hidden" value="'.$id.'" name="id">
        <br>
        <input type="submit" value="Delete Post" name="delete">
        </form>
        '
        );
    }
    if (isset($_POST['delete'])) {
        $delete_id = $_POST['id'];
        @mysql_query("DELETE FROM `forums` WHERE `id` = '$delete_id'");
        unset($_POST['delete']);
    }
}
?>
<br>
<?php
if ($id !== $delete_id) {
    $content = mysql_result(mysql_query("SELECT `content` FROM `forums` WHERE `id` = '$id'"), 0, 'content');
    echo ('<br>' . $content);
}
if ($id === $delete_id) {
    sprintf(
        'This post was deleted from the site successfully.
        <br><a href=board.php?id=%s>Refresh the page to remove this post box from your browser.</a>
        <br><br>',
        $classid
    );
}
?>
</div>
<?php } // endforeach ?>
</ul>

<?php include '../includes/overall/footer.php';?>
