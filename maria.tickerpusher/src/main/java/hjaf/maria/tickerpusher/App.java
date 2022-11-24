package hjaf.maria.tickerpusher;

import hjaf.maria.tickerpusher.model.TickerWrapper;
import hjaf.maria.tickerpusher.repository.TickerRepository;
import hjaf.maria.tickerpusher.repository.impl.TickerRepositoryMongo;
import hjaf.maria.tickerpusher.repository.impl.TickerRepositoryPrometheus;
import hjaf.maria.tickerpusher.service.DaggerServiceComponent;
import hjaf.maria.tickerpusher.service.MarketDataProvider;
import hjaf.maria.tickerpusher.service.ServiceComponent;
import hjaf.maria.tickerpusher.service.module.ServiceModule;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.knowm.xchange.ExchangeFactory;
import org.knowm.xchange.currency.CurrencyPair;
import org.knowm.xchange.dto.marketdata.Ticker;
import org.knowm.xchange.kraken.KrakenExchange;

import java.io.IOException;
import java.sql.Timestamp;
import java.util.concurrent.TimeUnit;

public class App {

    private static final Logger logger = LogManager.getLogger(App.class);

    public static void main(String[] args) {
        ServiceComponent serviceComponent = DaggerServiceComponent
                .builder()
                .serviceModule(
                        new ServiceModule(
                                ExchangeFactory.INSTANCE.createExchange(KrakenExchange.class.getName())
                        )
                )
                .build();

        //TickerRepository tickerRepository = new TickerRepositoryMongo("127.0.0.1", 27017, "maria-1", "tickers");
        TickerRepository tickerRepository = new TickerRepositoryPrometheus("127.0.0.1", 9091);
        MarketDataProvider marketDataProvider = serviceComponent.getMarketDataProvider();
        while (true) {
            try {
                TimeUnit.SECONDS.sleep(2);
            } catch (InterruptedException ex) {
                logger.info(ex);
                System.exit(0);
            }
            Ticker ticker = null;
            try {
                ticker = marketDataProvider.getTicker(CurrencyPair.BTC_USD);
            } catch (IOException ex) {
                logger.error(ex);
                continue;
            }
            tickerRepository.push(new TickerWrapper(ticker, new Timestamp(System.currentTimeMillis())));
            logger.info("Ticker pushed");
        }
    }
}
