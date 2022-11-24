package hjaf.maria.tickerpusher.repository.impl;

import hjaf.maria.tickerpusher.model.TickerWrapper;
import hjaf.maria.tickerpusher.repository.TickerRepository;
import io.prometheus.client.CollectorRegistry;
import io.prometheus.client.Gauge;
import io.prometheus.client.exporter.PushGateway;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.io.IOException;

public class TickerRepositoryPrometheus implements TickerRepository {

    private static final Logger logger = LogManager.getLogger(TickerRepositoryPrometheus.class);

    private PushGateway pushGateway;

    public TickerRepositoryPrometheus(String host, int port) {
        pushGateway = new PushGateway(host + ":" + port);
    }

    public void push(TickerWrapper tickerWrapper) {
        CollectorRegistry registry = new CollectorRegistry();
        Gauge open = Gauge.build().name("open").help("open").register(registry);
        Gauge ask = Gauge.build().name("ask").help("ask").register(registry);
        //Gauge askSize = Gauge.build().name("ask_size").help("ask_size").register(registry);
        Gauge bid = Gauge.build().name("bid").help("bid").register(registry);
        //Gauge bidSize = Gauge.build().name("bid_size").help("bid_size").register(registry);
        Gauge high = Gauge.build().name("high").help("high").register(registry);
        Gauge low = Gauge.build().name("low").help("low").register(registry);
        Gauge last = Gauge.build().name("last").help("last").register(registry);
        Gauge quoteVolume = Gauge.build().name("quote_volume").help("quote_volume").register(registry);
        Gauge volume = Gauge.build().name("volume").help("volume").register(registry);
        Gauge vwap = Gauge.build().name("vwap").help("vwap").register(registry);

        open.set(tickerWrapper.getTicker().getOpen().doubleValue());
        ask.set(tickerWrapper.getTicker().getAsk().doubleValue());
        //askSize.set(tickerWrapper.getTicker().getAskSize().doubleValue());
        bid.set(tickerWrapper.getTicker().getBid().doubleValue());
        //bidSize.set(tickerWrapper.getTicker().getBidSize().doubleValue());
        high.set(tickerWrapper.getTicker().getHigh().doubleValue());
        low.set(tickerWrapper.getTicker().getLow().doubleValue());
        last.set(tickerWrapper.getTicker().getLast().doubleValue());
        quoteVolume.set(tickerWrapper.getTicker().getQuoteVolume().doubleValue());
        volume.set(tickerWrapper.getTicker().getVolume().doubleValue());
        vwap.set(tickerWrapper.getTicker().getVwap().doubleValue());

        try {
            pushGateway.pushAdd(registry, "ticker");
        } catch (IOException ex) {
            logger.error("Prometheus PushGateway exception: " + ex.getMessage());
        }
    }
}
