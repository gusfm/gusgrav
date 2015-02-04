#ifndef GUSGRAV_SRC_UNIVERSE_MGR_H_
#define GUSGRAV_SRC_UNIVERSE_MGR_H_

int universe_mgr_init(const char *name, int sizeX, int sizeY);

void universe_mgr_terminate(void);

void universe_mgr_main_loop(void);

#endif /* GUSGRAV_SRC_UNIVERSE_MGR_H_ */
