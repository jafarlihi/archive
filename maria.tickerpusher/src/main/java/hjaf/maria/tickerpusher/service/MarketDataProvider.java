package hjaf.maria.tickerpusher.service;

import org.knowm.xchange.currency.CurrencyPair;
import org.knowm.xchange.dto.marketdata.OrderBook;
import org.knowm.xchange.dto.marketdata.Ticker;

import java.io.IOException;

public interface MarketDataProvider {
    OrderBook getOrderBook(CurrencyPair currencyPair) throws IOException;

    Ticker getTicker(CurrencyPair currencyPair) throws IOException;
}
