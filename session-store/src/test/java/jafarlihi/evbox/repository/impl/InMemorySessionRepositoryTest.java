package jafarlihi.evbox.repository.impl;

import jafarlihi.evbox.sessionstore.model.Session;
import jafarlihi.evbox.sessionstore.repository.impl.InMemorySessionRepository;
import org.junit.Test;

import java.time.*;
import java.util.NavigableSet;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.Matchers.equalTo;
import static org.junit.Assert.assertTrue;

public class InMemorySessionRepositoryTest {

    private static final Clock fixedClock = Clock.fixed(Instant.parse("2019-01-01T18:00:00.00Z"), ZoneId.of("UTC"));

    @Test
    public void testSavingSingleRecentSessionAndFetchingIt() {
        LocalDateTime chargeDateTime = LocalDateTime.parse("2019-01-01T17:59:50");
        String stationName = "EVB-1";
        Session session = new Session(chargeDateTime, stationName);

        InMemorySessionRepository inMemorySessionRepository = new InMemorySessionRepository(fixedClock);
        inMemorySessionRepository.save(session);
        NavigableSet<Session> result = inMemorySessionRepository.findLastMinuteSessionsByStation(stationName);

        assertThat(result.size(), equalTo(1));
        assertThat(result.last().getStation(), equalTo(stationName));
        assertThat(result.last().getTime(), equalTo(chargeDateTime));
    }

    @Test
    public void testSavingRecentAndExpiredSessionsAndFetchingThem() {
        LocalDateTime chargeDateTimeRecent1 = LocalDateTime.parse("2019-01-01T17:59:59");
        LocalDateTime chargeDateTimeRecent2 = LocalDateTime.parse("2019-01-01T17:59:01");
        LocalDateTime chargeDateTimeExpired1 = LocalDateTime.parse("2019-01-01T17:58:59");
        LocalDateTime chargeDateTimeExpired2 = LocalDateTime.parse("2018-01-01T17:59:59");

        String stationName = "EVB-1";
        Session recentSession1 = new Session(chargeDateTimeRecent1, stationName);
        Session recentSession2 = new Session(chargeDateTimeRecent2, stationName);
        Session expiredSession1 = new Session(chargeDateTimeExpired1, stationName);
        Session expiredSession2 = new Session(chargeDateTimeExpired2, stationName);

        InMemorySessionRepository inMemorySessionRepository = new InMemorySessionRepository(fixedClock);
        inMemorySessionRepository.save(recentSession1);
        inMemorySessionRepository.save(recentSession2);
        inMemorySessionRepository.save(expiredSession1);
        inMemorySessionRepository.save(expiredSession2);
        NavigableSet<Session> result = inMemorySessionRepository.findLastMinuteSessionsByStation(stationName);

        assertThat(result.size(), equalTo(2));
        assertTrue(result.stream().allMatch(s -> s.getStation().equals(stationName)));
        assertTrue(result.stream().anyMatch(s -> s.getTime().equals(chargeDateTimeRecent1)));
        assertTrue(result.stream().anyMatch(s -> s.getTime().equals(chargeDateTimeRecent2)));
    }

    @Test
    public void testSavingRecentSessionsOfMultipleStationsAndFetchingThem() {
        LocalDateTime chargeDateTimeRecent1 = LocalDateTime.parse("2019-01-01T17:59:59");
        LocalDateTime chargeDateTimeRecent2 = LocalDateTime.parse("2019-01-01T17:59:01");
        LocalDateTime chargeDateTimeRecent3 = LocalDateTime.parse("2019-01-01T17:59:30");
        LocalDateTime chargeDateTimeRecent4 = LocalDateTime.parse("2019-01-01T17:59:40");

        String stationName1 = "EVB-1";
        String stationName2 = "EVB-2";
        Session station1Session1 = new Session(chargeDateTimeRecent1, stationName1);
        Session station1Session2 = new Session(chargeDateTimeRecent2, stationName1);
        Session station2Session1 = new Session(chargeDateTimeRecent3, stationName2);
        Session station2Session2 = new Session(chargeDateTimeRecent4, stationName2);

        InMemorySessionRepository inMemorySessionRepository = new InMemorySessionRepository(fixedClock);
        inMemorySessionRepository.save(station1Session1);
        inMemorySessionRepository.save(station1Session2);
        inMemorySessionRepository.save(station2Session1);
        inMemorySessionRepository.save(station2Session2);
        NavigableSet<Session> station1Result = inMemorySessionRepository.findLastMinuteSessionsByStation(stationName1);
        NavigableSet<Session> station2Result = inMemorySessionRepository.findLastMinuteSessionsByStation(stationName2);

        assertThat(station1Result.size(), equalTo(2));
        assertThat(station2Result.size(), equalTo(2));
        assertTrue(station1Result.stream().allMatch(s -> s.getStation().equals(stationName1)));
        assertTrue(station2Result.stream().allMatch(s -> s.getStation().equals(stationName2)));
        assertTrue(station1Result.stream().anyMatch(s -> s.getTime().equals(chargeDateTimeRecent1)));
        assertTrue(station1Result.stream().anyMatch(s -> s.getTime().equals(chargeDateTimeRecent2)));
        assertTrue(station2Result.stream().anyMatch(s -> s.getTime().equals(chargeDateTimeRecent3)));
        assertTrue(station2Result.stream().anyMatch(s -> s.getTime().equals(chargeDateTimeRecent4)));
    }
}
