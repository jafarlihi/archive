package jafarlihi.evbox.sessionstore.model;

import com.fasterxml.jackson.annotation.JsonFormat;

import java.time.LocalDateTime;
import java.util.Objects;

public class Session {

    @JsonFormat(pattern = "yyyy.MM.dd'T'HH.mm.ss")
    private LocalDateTime time;
    private String station;

    public Session() {
    }

    public Session(LocalDateTime time) {
        this.time = time;
    }

    public Session(LocalDateTime time, String station) {
        this.time = time;
        this.station = station;
    }

    public LocalDateTime getTime() {
        return time;
    }

    public String getStation() {
        return station;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Session session = (Session) o;
        // Assuming that a given station won't have multiple charge sessions registered for the same exact time
        return Objects.equals(time, session.time) &&
                Objects.equals(station, session.station);
    }

    @Override
    public int hashCode() {
        return Objects.hash(time, station);
    }

    @Override
    public String toString() {
        return "Session{" +
                "time=" + time +
                ", station='" + station + '\'' +
                '}';
    }
}
