package hjaf.maria.tickerpusher.service.module;

import dagger.Module;
import dagger.Provides;
import org.knowm.xchange.Exchange;
import org.knowm.xchange.service.marketdata.MarketDataService;

import javax.inject.Singleton;

@Module
public class ServiceModule {

    private Exchange exchange;

    public ServiceModule(Exchange exchange) {
        this.exchange = exchange;
    }

    @Provides
    @Singleton
    public MarketDataService provideMarketDataService() {
        return exchange.getMarketDataService();
    }
}
