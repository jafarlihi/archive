package hjaf.maria.tickerpusher.model

import org.knowm.xchange.dto.marketdata.Ticker
import java.sql.Timestamp

data class TickerWrapper(val ticker: Ticker, val timestamp: Timestamp)