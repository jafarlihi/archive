package hjaf.maria.tickerpusher.repository;

import hjaf.maria.tickerpusher.model.TickerWrapper;

public interface TickerRepository {
    void push(TickerWrapper tickerWrapper);
}
