<?php
class AlbumOperations
{
    function __construct ()
    {
        self::albums_modal();
    }

    protected function pull_album_data()
    {
        $db = new Database();

        $statement = $db->pdo->query("SELECT * FROM albums");
        $albums = $statement->fetchAll();

        $statement = $db->pdo->query("SELECT * FROM album_images");
        $album_images = $statement->fetchAll();

        $albums = array($albums, $album_images);
        return $albums;
    }

    protected function albums_modal()
    {
        $header = <<<'EOT'
        <div class="modal fade" id="albumModal">
            <div class="modal-dialog" role="document">
                <div class="modal-content">
                    <div class="modal-header">
                        <button type="button" class="close" data-dismiss="modal"><span>&times;</span></button>
                        <h4 class="modal-title">Albums</h4>
                    </div>
                    <div class="modal-body">

EOT;

        $creator = <<<'EOT'
                        <div class="col-md-12">
                            <form method="POST" action="index.php">
                                <input type="hidden" name="newAlbum" value="true">
                                <input type="text" name="newAlbumTitle" placeholder="Name of the new album">
                                <button type="submit" class="btn btn-primary btn-sm">Create an album</button>
                            </form>
                        </div>

EOT;

        $albumTemplate = <<<'EOT'
                        <div class="col-md-12">
                            <hr style="width: 100%; color: black; height: 1px; background-color:black;">
                            <text style="font-size: 10px;">Album: </text><span class="label label-success">%1$s</span><br><br>
                            %2$s
                        </div>

EOT;

        $imageTemplate = <<<'EOT'
                        <div class="col-lg-4 col-md-4 col-xs-6">
                            <a class="thumbnail" href="images/full/%1$s.jpeg" data-toggle="modal">
                                <img class="img-responsive" src="images/thumb/%1$s.jpeg">
                            </a>
                        </div>

EOT;

        $footer = <<<'EOT'
                    <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
                </div>
            </div>
        </div>
    </div>

EOT;

        $albums = self::pull_album_data();

        if (empty($albums[0])) {
            echo $header . $creator . 'No albums were found.<br><br>' . $footer;
            return false;
        }

        $images = '';

        echo $header . $creator;

        foreach ($albums[0] as $currentAlbum) {
            foreach ($albums[1] as $album_images) {
                if ($currentAlbum['id'] == $album_images['album_id']) {
                    $image = sprintf($imageTemplate, $album_images['image_id']);
                    $images = $images . $image;
                }
            }

            $album = sprintf($albumTemplate, $currentAlbum['title'], $images);

            $images = '';

            echo $album;
        }

        /*
        foreach ($albums as $albumData) {
            $imageIDArray = explode(", ", $albumData['image_ids']);

            foreach ($imageIDArray as $imageID) {
                if ($imageID > 0) {
                    $image = sprintf($imageTemplate, $imageID);
                    $images = $images . $image;
                }
            }


            if ($images != '') {
                $album = sprintf($albumTemplate, $albumData['title'], $images);
            } else {
                $album = sprintf($albumTemplate, $albumData['title'], 'This album contains no images.<br><br>');
            }
            $images = '';

            echo $album;
        }
        */

        echo $footer;
    }

    public function new_album($POST)
    {
        $header = <<<'EOT'
        <div class="modal fade" id="albumCreatorModal">
            <div class="modal-dialog modal-lg" role="document">
                <div class="modal-content">
                    <div class="modal-header">
                        <button type="button" class="close" data-dismiss="modal"><span>&times;</span></button>
                        <h4 class="modal-title">Creating a new album titled "%1$s"</h4>
                    </div>
                    <div class="modal-body">
                    <h5 class="modal-title">Choose images to add to the new album:</h5><br>
                    <form action="index.php" method="POST">
                        <input type="hidden" name="controlFieldAlbumCreated" value="submitted">
                        <input type="hidden" name="newAlbumTitle" value="%1$s">
                        <select multiple="multiple" id="selectImages" name="selectedImages[]" class="image-picker">

EOT;

        $header = sprintf($header, $POST['newAlbumTitle']);

        $footer = <<<'EOT'
                        </select>
                        <button type="submit" class="btn btn-primary">Create Album</button>
                        <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
                    </form>
                </div>
            </div>
        </div>
    </div>
    <script>$("select").imagepicker();</script>

EOT;

        $imageTemplate = <<<'EOT'
                    <option data-img-src="images/thumb/%1$s.jpeg" value="%1$s">Image ID %1$s</option>
EOT;

        $allImageData = self::return_all_images();
        $allImages = '';
        $imageHTML = '';

        foreach ($allImageData as $image) {
            $imageHTML = sprintf($imageTemplate, $image['id']);
            $allImages = $allImages . $imageHTML;
        }

        echo $header . $allImages . $footer;
    }

    public function create_album($POST)
    {
        $selectedImages = $POST['selectedImages'];
        $albumTitle = $POST['newAlbumTitle'];

        $db = new Database();

        $lastID = 0;

        $statement = $db->pdo->query('SELECT * FROM albums ORDER BY id DESC LIMIT 1');
        while ($row = $statement->fetch()) {
            $lastID = $row['id'];
        }

        $currentID = $lastID + 1;

        $query = "INSERT INTO `albums` (id, title) VALUES (:id, :title)";
        $stmt = $db->pdo->prepare($query);
        $stmt->bindValue(':id', $currentID, PDO::PARAM_INT);
        $stmt->bindValue(':title', $albumTitle, PDO::PARAM_STR);
        $stmt->execute();

        foreach ($selectedImages as $currentImage) {
            $statement = $db->pdo->prepare('INSERT INTO album_images (album_id, image_id) VALUES (:album_id, :image_id)');
            $statement->execute(array(
                "album_id" => $currentID,
                "image_id" => $currentImage
            ));
        }

        $successMessage = <<<'EOT'
        <div class="alert alert-success alert-dismissible col-md-6" role="alert">
          <button type="button" class="close" data-dismiss="alert"><span>&times;</span></button>
          <strong>Success!</strong> New album was created!
        </div>
EOT;

        echo $successMessage;
    }

    protected function return_all_images()
    {
        $db = new Database();

        $statement = $db->pdo->query("SELECT * FROM images");
        $result = $statement->fetchAll();

        return $result;
    }
}
