package jafarlihi.evbox.sessionstore.config;

import jafarlihi.evbox.sessionstore.repository.SessionRepository;
import jafarlihi.evbox.sessionstore.repository.impl.InMemorySessionRepository;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

import java.time.Clock;

@Configuration
public class ApplicationConfiguration {

    @Bean
    public SessionRepository getSessionRepository() {
        return new InMemorySessionRepository(Clock.systemDefaultZone());
    }
}
