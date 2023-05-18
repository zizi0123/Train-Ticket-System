#include "train.h"

Train::Train(): all_trains("train_index","train_seq"), released_trains("released_index","released_seq"),
                station_to_trains("station_index","station_seq") {}
