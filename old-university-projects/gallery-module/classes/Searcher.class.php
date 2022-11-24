<?php
class Searcher
{
    protected $searchQuery;

    function __construct($POST)
    {
        $this->searchQuery = $POST['keyword'];

        $results = self::return_matching_rows($this->searchQuery);
        Displayer::display($results);
    }

    protected function return_matching_rows($searchQuery)
    {
        $db = new Database();

        $statement = $db->pdo->prepare("SELECT * FROM images WHERE tags LIKE :keyword");
        $statement->execute(array(
            ":keyword" => "%" . $searchQuery . "%"
        ));

        $result = $statement->fetchAll();
        return $result;
    }
}
