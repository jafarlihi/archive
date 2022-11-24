<?php
class Displayer
{
    public static function display($resultArray)
    {
        $header = <<<'EOT'
        <div class="modal fade" id="galleryModal">
            <div class="modal-dialog" role="document">
                <div class="modal-content">
                    <div class="modal-header">
                        <button type="button" class="close" data-dismiss="modal"><span>&times;</span></button>
                        <h4 class="modal-title">Gallery</h4>
                    </div>
                    <div class="modal-body">
                        <div class="row">
                            <div class="col-lg-12">

EOT;

        $image = <<<'EOT'
                                <div class="col-lg-4 col-md-4 col-xs-6">
                                    <a class="thumbnail" href="%1$s" data-toggle="modal">
                                        <img class="img-responsive" src="%2$s">
                                        Tags: %3$s
                                    </a>
                                </div>

EOT;

        $footer = <<<'EOT'
                            </div>
                        </div>

                        <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
                    </div>
                </div>
            </div>
        </div>
EOT;

        $emptyControl = 0;

        echo $header;

        foreach ($resultArray as $id) {
            $emptyControl = 1;
            $tagArray = json_decode($id['tags']);
            $tags = implode(', ', $tagArray);

            $imageHTML = sprintf(
                $image,
                'images/full/' . $id['id'] . '.jpeg',
                'images/thumb/' . $id['id'] . '.jpeg',
                $tags);

            echo $imageHTML;
        }

        if ($emptyControl == 0) {
            echo 'No images found. <br>
            Specified keyword is not present in any of the tags.';
        }

        echo $footer;
    }
}
