package jafarlihi.evbox.sessionstore.repository.impl;

import jafarlihi.evbox.sessionstore.model.Session;
import jafarlihi.evbox.sessionstore.repository.SessionRepository;

import java.time.Clock;
import java.time.LocalDateTime;
import java.util.Comparator;
import java.util.NavigableSet;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentSkipListSet;

public class InMemorySessionRepository implements SessionRepository {

    private final Clock clock;
    private final ConcurrentHashMap<String, ConcurrentSkipListSet<Session>> sessions;

    public InMemorySessionRepository(Clock clock) {
        this.clock = clock;
        this.sessions = new ConcurrentHashMap<>();
    }

    public void save(Session session) {
        sessions.computeIfAbsent(
                session.getStation(),
                k -> new ConcurrentSkipListSet<>(Comparator.comparing(Session::getTime))
        ).add(session);
    }

    public NavigableSet<Session> findLastMinuteSessionsByStation(String station) {
        return sessions.computeIfAbsent(
                station,
                k -> new ConcurrentSkipListSet<>(Comparator.comparing(Session::getStation))
        ).tailSet(new Session(LocalDateTime.now(clock).minusMinutes(1)));
    }
}
