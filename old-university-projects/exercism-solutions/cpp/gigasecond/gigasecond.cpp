#include "gigasecond.h"

namespace gigasecond {

boost::posix_time::ptime advance(boost::posix_time::ptime input) {
    return input + boost::posix_time::seconds(1000000000);
}

}
