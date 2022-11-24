package jafarlihi.evbox.sessionstore.repository;

import jafarlihi.evbox.sessionstore.model.Session;

import java.util.NavigableSet;

public interface SessionRepository {

    void save(Session session);

    NavigableSet<Session> findLastMinuteSessionsByStation(String station);
}
