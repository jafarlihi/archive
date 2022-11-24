package hjaf.maria.tickerpusher.service.impl;

import org.knowm.xchange.currency.CurrencyPair;
import org.knowm.xchange.dto.marketdata.OrderBook;
import org.knowm.xchange.dto.marketdata.Ticker;
import org.knowm.xchange.service.marketdata.MarketDataService;

import javax.inject.Inject;
import java.io.IOException;

public class MarketDataProvider implements hjaf.maria.tickerpusher.service.MarketDataProvider {

    private final MarketDataService marketDataService;

    @Inject
    public MarketDataProvider(MarketDataService marketDataService) {
        this.marketDataService = marketDataService;
    }

    public OrderBook getOrderBook(CurrencyPair currencyPair) throws IOException {
        return marketDataService.getOrderBook(currencyPair);
    }

    public Ticker getTicker(CurrencyPair currencyPair) throws IOException {
        return marketDataService.getTicker(currencyPair);
    }
}
