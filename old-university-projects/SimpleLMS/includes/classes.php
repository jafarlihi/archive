<?php namespace SimpleLMS;

class Classes
{
    public function fetchAll()
    {
        global $pdo;

        $query = $pdo->prepare("SELECT * FROM classes");
        $query->execute();

        return $query->fetchAll();
    }
}
