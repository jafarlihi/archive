package hjaf.maria.tickerpusher.service;

import dagger.Component;
import hjaf.maria.tickerpusher.service.impl.MarketDataProvider;
import hjaf.maria.tickerpusher.service.module.ServiceModule;

import javax.inject.Singleton;

@Singleton
@Component(modules = ServiceModule.class)
public interface ServiceComponent {
    MarketDataProvider getMarketDataProvider();
}
