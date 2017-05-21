INCLUDE_DIRECTORIES(${COMMON})
INCLUDE_DIRECTORIES(${PYTHON27})

SET(DATA_SRC
        BoostExport.h
        IDataFeed.h
        Resolution.h
        DataFeed.cpp DataFeed.h
        DataFeed_OHLCV.cpp DataFeed_OHLCV.h
        DataInitializer.cpp DataInitializer.h
        DataSlice.cpp DataSlice.h
        Indicator.cpp Indicator.h
        Indicator_SMA.cpp Indicator_SMA.h
        OHLC.cpp OHLC.h
        OHLCV.cpp OHLCV.h
        OHLCVReader.cpp OHLCVReader.h
        OHLCVReader_Py.cpp OHLCVReader_Py.h
        Symbol.cpp Symbol.h
        DataSeries.cpp DataSeries.h)

ADD_LIBRARY(Data SHARED ${DATA_SRC})