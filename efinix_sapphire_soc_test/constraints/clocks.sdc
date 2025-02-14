# author      : siarhei baldzenka
# data        : 10.02.2025
# e-mail      : venera.electronica@gmail.com

create_clock -period 40 [get_ports {pll_clk_soc}]
create_clock -period 20 [get_ports {pll_clk_50}]