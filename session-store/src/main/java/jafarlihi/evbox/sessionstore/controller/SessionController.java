package jafarlihi.evbox.sessionstore.controller;

import jafarlihi.evbox.sessionstore.model.Session;
import jafarlihi.evbox.sessionstore.model.SummaryResponse;
import jafarlihi.evbox.sessionstore.repository.SessionRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

@RestController
public class SessionController {

    private final SessionRepository sessionRepository;

    @Autowired
    public SessionController(SessionRepository sessionRepository) {
        this.sessionRepository = sessionRepository;
    }

    @RequestMapping(value = "/chargingSession", method = RequestMethod.PUT)
    public void putSession(@RequestBody Session session) {
        sessionRepository.save(session);
    }

    @RequestMapping(value = "/summary", method = RequestMethod.GET)
    public SummaryResponse getSummary(@RequestParam String station) {
        return new SummaryResponse(sessionRepository.findLastMinuteSessionsByStation(station).size());
    }
}
