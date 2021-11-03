#define set_bit(reg,pin) {reg |= (1<<pin);}
#define clear_bit(reg,pin) {reg &= ~(1<<pin);}
#define get_bit(reg,pin) {(reg & 1<<(pin))>> pin;}
#define toggle_bit(reg,pin) {reg ^= (1<<(pin);}
