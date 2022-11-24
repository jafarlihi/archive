<!DOCTYPE html>
<html>
<head>
    <meta http-equiv="cache-control" content="max-age=0">
    <meta http-equiv="cache-control" content="no-cache">
    <meta http-equiv="expires" content="0">
    <meta http-equiv="pragma" content="no-cache">

    <title>gallery-module Demo</title>

    <link rel="stylesheet" type="text/css" href="assets/bootstrap/css/bootstrap.min.css">
    <link rel="stylesheet" type="text/css" href="assets/bootstrap-tags/bootstrap-tagsinput.css">
    <link rel="stylesheet" type="text/css" href="assets/image-picker/image-picker.css">
</head>
<body>
    <script src="assets/jquery/jquery-2.2.4.min.js"></script>
    <script src="assets/bootstrap/js/bootstrap.min.js"></script>
    <script src="assets/bootstrap-tags/bootstrap-tagsinput.min.js"></script>
    <script src="assets/image-picker/image-picker.min.js"></script>
    <script src="assets/main.js"></script>

<?php
spl_autoload_register(function($className) {
    include 'classes/' . $className . '.class.php';
});

if (isset($_POST['controlField'])) {
    $uploader = new UploadOperations($_POST, $_FILES);
}

if (isset($_POST['controlFieldSearch'])) {
    $searcher = new Searcher($_POST);
}

if (isset($_POST['albumButtonClicked'])) {
    $albumer = new AlbumOperations();
}

if (isset($_POST['newAlbum'])) {
    AlbumOperations::new_album($_POST);
}

if (isset($_POST['controlFieldAlbumCreated'])) {
    AlbumOperations::create_album($_POST);
}
?>

    <br>
    <div class="col-md-12">
        <button type="button" class="btn btn-primary btn-lg" data-toggle="modal" data-target="#uploadModal">Upload</button>
        <button type="button" class="btn btn-primary btn-lg" data-toggle="modal" data-target="#searchModal">Search</button>
        <form method="POST" action="index.php" style="display: inline;"><button type="submit" class="btn btn-primary btn-lg" name="albumButtonClicked">Albums</button></form>
    </div>

    <div class="col-md-12">
        <br>
        <hr>
        <text style="color: red;"><b><u>QU InetTech 2016 class project</u></b></text><br>
            <b>Project:</b> 3-piece image bank, as per instructor's request.<br>
            <b>Part 1:</b> Image upload. Converts all provided images to JPEG, stores thumbnail and full-sized copy.<br>
            Utilizes MySQL for storage of image ID and associated keywords.<br>
            <b>Part 2:</b> Gallery search. Provides interface for fetching uploaded images by specifying a keyword.<br>
            Images with keywords that are full or partial search query hits are returned.<br>
            <b>Part 3:</b> Album creation. Provides interface for categorizing multiple images under a single album.<br>
            Stores album details on a separate database table.
    </div>

    <div class="modal fade" tabindex="-1" role="dialog" id="uploadModal">
        <div class="modal-dialog" role="document">
            <div class="modal-content">
                <div class="modal-header">
                    <button type="button" class="close" data-dismiss="modal"><span>&times;</span></button>
                    <h4 class="modal-title">Image Upload</h4>
                </div>
                <div class="modal-body">
                    <form class="form-inline" method="POST" action="index.php" enctype="multipart/form-data">
                        <div class="input-group col-md-12">
                            <label class="input-group-btn">
                                <span class="btn btn-primary col-md-12">
                                    Browse <input type="file" name="image" style="display: none;" accept="image/*">
                                </span>
                            </label>
                            <input type="text" class="form-control" readonly>
                        </div>

                        <br><br>
                        <label for="tags">Tags:</label>
                        <div class="input-group">
                            <input id="tags" name="tags" type="text" data-role="tagsinput">
                        </div>

                        <input type="hidden" name="controlField" value="submitted">

                        <br><br>
                        <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
                        <button type="submit" class="btn btn-primary">Upload</button>
                    </form>
                </div>
            </div>
        </div>
    </div>

    <div class="modal fade" tabindex="-1" role="dialog" id="searchModal">
        <div class="modal-dialog" role="document">
            <div class="modal-content">
                <div class="modal-header">
                    <button type="button" class="close" data-dismiss="modal"><span>&times;</span></button>
                    <h4 class="modal-title">Search Images</h4>
                </div>
                <div class="modal-body">
                    <form class="form-inline" method="POST" action="index.php" enctype="multipart/form-data">
                        <label for="keyword">Keyword:</label>
                        <div class="input-group">
                            <input id="keyword" name="keyword" type="text">
                        </div>

                        <input type="hidden" name="controlFieldSearch" value="submitted">

                        <br><br>
                        <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
                        <button type="submit" class="btn btn-primary">Search</button>
                    </form>
                </div>
            </div>
        </div>
    </div>
</body>
</html>
