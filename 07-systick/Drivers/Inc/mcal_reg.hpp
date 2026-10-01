#ifndef INC_MCAL_REG_HPP
#define INC_MCAL_REG_HPP

#include <cstdint>
#include "mcal_reg_access.hpp"

namespace mcal
{
    namespace reg
    {
        constexpr uint32_t BIT(uint32_t pos)
        {
            return (1U << pos);
        }

        // global base address
        constexpr std::uint32_t periph_base = 0x40000000U;

        // Individual unit base addresses
        constexpr std::uint32_t apb1periph_base = periph_base;
        constexpr std::uint32_t apb2periph_base = periph_base + 0x00010000U;
        constexpr std::uint32_t ahb1periph_base = periph_base + 0x00020000U;

        constexpr std::uint32_t rcc_base        = ahb1periph_base + 0x00003800U;
      
        constexpr std::uint32_t ahb1enr =	rcc_base + 0x30;
        constexpr std::uint32_t ahb2enr =	rcc_base + 0x34;
        constexpr std::uint32_t apb1enr =	rcc_base + 0x40;
        constexpr std::uint32_t apb2enr =	rcc_base + 0x44;

        constexpr std::uint32_t systick_base    = 0xE000E010;
        constexpr std::uint32_t nvic_base       = 0xE000E100;
      
        constexpr std::uint32_t gpioa_base      = ahb1periph_base +  0x0000;
        constexpr std::uint32_t gpiob_base      = ahb1periph_base +  0x0400;
        constexpr std::uint32_t gpioc_base      = ahb1periph_base +  0x0800;
        constexpr std::uint32_t gpiod_base      = ahb1periph_base +  0x0C00;
        constexpr std::uint32_t gpioe_base      = ahb1periph_base +  0x1000;

        constexpr std::uint32_t usart1_base     = apb2periph_base +  0x1000;
        constexpr std::uint32_t usart2_base     = apb1periph_base +  0x4400;
        constexpr std::uint32_t usart6_base     = apb2periph_base +  0x1400;

        constexpr std::uint32_t adc1_base       = apb2periph_base + 0x2000;

        constexpr std::uint32_t spi1_base       = apb2periph_base + 0x3000;
        constexpr std::uint32_t spi2_base       = apb1periph_base + 0x3800;
        constexpr std::uint32_t spi3_base       = apb1periph_base + 0x3C00;
        constexpr std::uint32_t spi4_base       = apb2periph_base + 0x3400;

        constexpr std::uint32_t i2c1_base       = apb1periph_base + 0x5400;
        constexpr std::uint32_t i2c2_base       = apb1periph_base + 0x5800;
        constexpr std::uint32_t i2c3_base       = apb1periph_base + 0x5C00;
        
        // Port registers.
        namespace gpio
        {
            namespace offset
            {
                constexpr std::uint32_t moder       = 0x00;
                constexpr std::uint32_t otyper      = 0x04;
                constexpr std::uint32_t ospeedr     = 0x08;
                constexpr std::uint32_t pupdr       = 0x0C;  
                constexpr std::uint32_t idr         = 0x10;  
                constexpr std::uint32_t odr         = 0x14;  
                constexpr std::uint32_t bsrr        = 0x18;  
                constexpr std::uint32_t lckr        = 0x1C;  
                constexpr std::uint32_t afrl        = 0x20;  
                constexpr std::uint32_t afrh        = 0x24;  
            } // offset

            namespace altfn
            {
                constexpr uint8_t pa2_usart2_tx = 7U;
                constexpr uint8_t pa3_usart2_rx = 7U;
            } // namespace altfn

        } // namespace gpio



        namespace usart
        {
            // USART register offsets
            namespace offset
            {
                constexpr std::uint32_t sr         = 0x00;
                constexpr std::uint32_t dr         = 0x04;
                constexpr std::uint32_t brr        = 0x08;
                constexpr std::uint32_t cr1        = 0x0c;
                constexpr std::uint32_t cr2        = 0x10;
                constexpr std::uint32_t cr3        = 0x14;
                constexpr std::uint32_t gtpr       = 0x18;
            }

            /// Bit positions (for shift operations and mask generation)
            namespace bitpos
            {
                namespace cr1
                {
                    constexpr uint32_t sbk          = 0;    ///< Send break
                    constexpr uint32_t rwu          = 1;    ///< Receiver wakeup
                    constexpr uint32_t re           = 2;    ///< Receiver enable
                    constexpr uint32_t te           = 3;    ///< Transmitter enable
                    constexpr uint32_t idleie       = 4;    ///< IDLE interrupt enable
                    constexpr uint32_t rxneie       = 5;    ///< RX not empty interrupt enable
                    constexpr uint32_t tcie         = 6;    ///< Transmission complete interrupt enable
                    constexpr uint32_t txeie        = 7;    ///< TX empty interrupt enable
                    constexpr uint32_t peie         = 8;    ///< Parity error interrupt enable
                    constexpr uint32_t ps           = 9;    ///< Parity selection
                    constexpr uint32_t pce          = 10;   ///< Parity control enable
                    constexpr uint32_t wake         = 11;   ///< Wakeup method
                    constexpr uint32_t m            = 12;   ///< Word length
                    constexpr uint32_t ue           = 13;   ///< USART enable
                } // namespace cr1

                namespace sr
                {
                    constexpr uint32_t pe           = 0;
                    constexpr uint32_t fe           = 1;
                    constexpr uint32_t nf           = 2;
                    constexpr uint32_t ore          = 3;
                    constexpr uint32_t idle         = 4;
                    constexpr uint32_t rxne         = 5;
                    constexpr uint32_t tc           = 6;
                    constexpr uint32_t txe          = 7;
                    constexpr uint32_t busy         = 8;
                } // namespace sr1
            } //namespace bitpos
            
            namespace mask
            {
                namespace cr1
                {
                    constexpr uint32_t sbk      = BIT(bitpos::cr1::sbk);
                    constexpr uint32_t rwu      = BIT(bitpos::cr1::rwu);
                    constexpr uint32_t re       = BIT(bitpos::cr1::re);
                    constexpr uint32_t te       = BIT(bitpos::cr1::te);
                    constexpr uint32_t idleie   = BIT(bitpos::cr1::idleie);
                    constexpr uint32_t rxneie   = BIT(bitpos::cr1::rxneie);
                    constexpr uint32_t tcie     = BIT(bitpos::cr1::tcie);
                    constexpr uint32_t txeie    = BIT(bitpos::cr1::txeie);
                    constexpr uint32_t peie     = BIT(bitpos::cr1::peie);
                    constexpr uint32_t ps       = BIT(bitpos::cr1::ps);
                    constexpr uint32_t pce      = BIT(bitpos::cr1::pce);
                    constexpr uint32_t wake     = BIT(bitpos::cr1::wake);
                    constexpr uint32_t m        = BIT(bitpos::cr1::m);
                    constexpr uint32_t ue       = BIT(bitpos::cr1::ue);
                } // namespace cr1

                namespace sr
                {
                    constexpr uint32_t pe       = BIT(bitpos::sr::pe);
                    constexpr uint32_t fe       = BIT(bitpos::sr::fe);
                    constexpr uint32_t nf       = BIT(bitpos::sr::nf);
                    constexpr uint32_t ore      = BIT(bitpos::sr::ore);
                    constexpr uint32_t idle     = BIT(bitpos::sr::idle);
                    constexpr uint32_t rxne     = BIT(bitpos::sr::rxne);
                    constexpr uint32_t tc       = BIT(bitpos::sr::tc);
                    constexpr uint32_t txe      = BIT(bitpos::sr::txe);
                    constexpr uint32_t busy     = BIT(bitpos::sr::busy);
                } // namespace sr
            } // namespace mask
        } // namespace uart

        namespace nvic
        {
            // NVIC register offsets
            namespace offset
            {
                constexpr std::uint32_t iser = 0x000; // Interrupt Set Enable Register
                constexpr std::uint32_t icer = 0x080; // Interrupt Clear Enable Register
                constexpr std::uint32_t ispr = 0x100; // Interrupt Set Pending Register
                constexpr std::uint32_t icpr = 0x180; // Interrupt Clear Pending Register
                constexpr std::uint32_t iabr = 0x200; // Interrupt Active Bit Register
                constexpr std::uint32_t ipr = 0x300;  // Interrupt Priority Register
            } // namespace oofset

            // Interrupt numbers for STM32F401
            enum class Irq : std::uint8_t
            {
                WWDG                = 0,
                PVD                 = 1,
                TAMP_STAMP          = 2,
                RTC_SKUP            = 3,
                FLASH               = 4,
                RCC                 = 5,
                EXTI0               = 6,
                EXTI1               = 7,
                EXTI2               = 8,
                EXTI3               = 9,
                EXTI4               = 10,
                DMA1_Stream0        = 11,
                DMA1_Stream1        = 12,
                DMA1_Stream2        = 13,
                DMA1_Stream3        = 14,
                DMA1_Stream4        = 15,
                DMA1_Stream5        = 16,
                DMA1_Stream6        = 17,
                ADC                 = 18,
                EXTI_9_5            = 23,
                TIM1_BRK_TIM9       = 24,
                TIM1_UP_TIM10       = 25,
                TIM1_TRG_COM_TIM11  = 26,
                TIM1_CC             = 27,
                TIM2                = 28,
                TIM3                = 29,
                TIM4                = 30,
                I2C1_EV             = 31,
                I2C1_ER             = 32,
                I2C2_EV             = 33,
                I2C2_ER             = 34,
                SPI1                = 35,
                SPI2                = 36,
                USART1              = 37,
                USART2              = 38,
                EXTI15_10           = 40,
                RTC_Alarm           = 41,
                OTG_FS_WKUP         = 42,
                DMA1_Stream7        = 47,
                SDIO                = 49,
                TIM5                = 50,
                SPI3                = 51,
                DMA2_Stream0        = 56,
                DMA2_Stream1        = 57,
                DMA2_Stream2        = 58,
                DMA2_Stream3        = 59,
                DMA2_Stream4        = 60,
                OTG_FS              = 67,
                DMA2_Stream5        = 68,
                DMA2_Stream6        = 69,
                DMA2_Stream7        = 70,
                USART6              = 71,
                I2C3_EV             = 72,
                I2C3_ER             = 73,
                FPU                 = 81,
                SPI4                = 84
            };

            // Priority grouping configuration
            enum class PriorityGroup : std::uint8_t
            {
                Group4 = 3, // 4 bits for preemption, 0 bits for subpriority
                Group3 = 4, // 3 bits for preemption, 1 bit for subpriority
                Group2 = 5, // 2 bits for preemption, 2 bits for subpriority
                Group1 = 6, // 1 bit  for preemption, 3 bits for subpriority
                Group0 = 7  // 0 bits for preemption, 4 bits for subpriority
            };
        } // namespace nvic

        namespace systick
        {
            namespace offset
            {
                constexpr std::uint32_t ctrl        = 0x00;
                constexpr std::uint32_t load        = 0x04;
                constexpr std::uint32_t val         = 0x08;
                constexpr std::uint32_t calib       = 0x0C;
            }
            
            namespace bitpos
            {
                namespace ctrl
                {
                    constexpr std::uint32_t enable      = 0;
                    constexpr std::uint32_t tickint     = 1;
                    constexpr std::uint32_t clksource   = 2;
                    constexpr std::uint32_t countflag   = 16;
                }
            } // namespace bitpos

            namespace mask
            {
                namespace ctrl
                {
                    constexpr std::uint32_t enable      = (1U << bitpos::ctrl::enable);
                    constexpr std::uint32_t tickint     = (1U << bitpos::ctrl::tickint);
                    constexpr std::uint32_t clksource   = (1U << bitpos::ctrl::clksource);
                    constexpr std::uint32_t countflag   = (1U << bitpos::ctrl::countflag);
                }
            } // namespace mask
        } // namespace systick

        namespace adc
        {
            namespace offset
            {
                constexpr std::uint32_t sr          = 0x00;
                constexpr std::uint32_t cr1         = 0x04;
                constexpr std::uint32_t cr2         = 0x08;
                constexpr std::uint32_t smpr1       = 0x0C;
                constexpr std::uint32_t smpr2       = 0x10;
                constexpr std::uint32_t jofr1       = 0x14;
                constexpr std::uint32_t jofr2       = 0x18;
                constexpr std::uint32_t jofr3       = 0x1C;
                constexpr std::uint32_t jofr4       = 0x20;
                constexpr std::uint32_t htr         = 0x24;
                constexpr std::uint32_t ltr         = 0x28;
                constexpr std::uint32_t sqr1        = 0x2C;
                constexpr std::uint32_t sqr2        = 0x30;
                constexpr std::uint32_t sqr3        = 0x34;
                constexpr std::uint32_t jsqr        = 0x38;
                constexpr std::uint32_t jdr1        = 0x3C;
                constexpr std::uint32_t jdr2        = 0x40;
                constexpr std::uint32_t jdr3        = 0x44;
                constexpr std::uint32_t jdr4        = 0x48;
                constexpr std::uint32_t dr          = 0x4C;
            }

            namespace bitpos
            {
                namespace cr1
                {
                    constexpr std::uint32_t awdch       = 0;
                    constexpr std::uint32_t eocie       = 5;
                    constexpr std::uint32_t awdie       = 6;
                    constexpr std::uint32_t jeocie      = 7;
                    constexpr std::uint32_t scan        = 8;
                    constexpr std::uint32_t awdsgl      = 9;
                    constexpr std::uint32_t jauto       = 10;
                    constexpr std::uint32_t discen      = 11;
                    constexpr std::uint32_t jdiscen     = 12;
                    constexpr std::uint32_t disnum      = 13;
                    constexpr std::uint32_t jawden      = 22;
                    constexpr std::uint32_t awden       = 23;
                    constexpr std::uint32_t res         = 24;
                    constexpr std::uint32_t ovrie       = 26;
                }

                namespace cr2
                {
                    constexpr std::uint32_t adon        = 0;
                    constexpr std::uint32_t cont        = 1;
                    constexpr std::uint32_t dma         = 8;
                    constexpr std::uint32_t align       = 11;
                    constexpr std::uint32_t swstart     = 30;
                }

                namespace sr
                {
                    constexpr std::uint32_t awd         = 0;
                    constexpr std::uint32_t eoc         = 1;
                    constexpr std::uint32_t jeoc        = 2;
                    constexpr std::uint32_t jstrt       = 3;
                    constexpr std::uint32_t strt        = 4;
                    constexpr std::uint32_t ovr         = 5;
                }
            }

            namespace mask
            {
                namespace cr1
                {
                    constexpr std::uint32_t awdch       = (0x1FU << bitpos::cr1::awdch);
                    constexpr std::uint32_t eocie       = (1U << bitpos::cr1::eocie);
                    constexpr std::uint32_t awdie       = (1U << bitpos::cr1::awdie);
                    constexpr std::uint32_t jeocie      = (1U << bitpos::cr1::jeocie);
                    constexpr std::uint32_t scan        = (1U << bitpos::cr1::scan);
                    constexpr std::uint32_t awdsgl      = (1U << bitpos::cr1::awdsgl);
                    constexpr std::uint32_t jauto       = (1U << bitpos::cr1::jauto);
                    constexpr std::uint32_t discen      = (1U << bitpos::cr1::discen);
                    constexpr std::uint32_t jdiscen     = (1U << bitpos::cr1::jdiscen);
                    constexpr std::uint32_t disnum      = (7U << bitpos::cr1::disnum);
                    constexpr std::uint32_t jawden      = (1U << bitpos::cr1::jawden);
                    constexpr std::uint32_t awden       = (1U << bitpos::cr1::awden);
                    constexpr std::uint32_t res         = (3U << bitpos::cr1::res);
                    constexpr std::uint32_t ovrie       = (1U << bitpos::cr1::ovrie);
                }

                namespace cr2
                {
                    constexpr std::uint32_t adon        = (1U << bitpos::cr2::adon);
                    constexpr std::uint32_t cont        = (1U << bitpos::cr2::cont);
                    constexpr std::uint32_t dma         = (1U << bitpos::cr2::dma);
                    constexpr std::uint32_t align       = (1U << bitpos::cr2::align);
                    constexpr std::uint32_t swstart     = (1U << bitpos::cr2::swstart);
                }

                namespace sr
                {
                    constexpr std::uint32_t awd         = (1U << bitpos::sr::awd);
                    constexpr std::uint32_t eoc         = (1U << bitpos::sr::eoc);
                    constexpr std::uint32_t jeoc        = (1U << bitpos::sr::jeoc);
                    constexpr std::uint32_t jstrt       = (1U << bitpos::sr::jstrt);
                    constexpr std::uint32_t strt        = (1U << bitpos::sr::strt);
                    constexpr std::uint32_t ovr         = (1U << bitpos::sr::ovr);
                }
            }
        } // namespace adc

        namespace spi
        {
            namespace offset
            {
                constexpr std::uint32_t cr1             = 0x00;
                constexpr std::uint32_t cr2             = 0x04;
                constexpr std::uint32_t sr              = 0x08;
                constexpr std::uint32_t dr              = 0x0C;
                constexpr std::uint32_t crcpr           = 0x10;
                constexpr std::uint32_t rxcrcr          = 0x14;
                constexpr std::uint32_t txcrcr          = 0x18;
                constexpr std::uint32_t i2scfgr         = 0x1C;
                constexpr std::uint32_t i2spr           = 0x20;
            } // namespace offset

            namespace bitpos
            {
                namespace cr1
                {
                    constexpr std::uint32_t cpha        = 0U;
                    constexpr std::uint32_t cpol        = 1U;
                    constexpr std::uint32_t mstr        = 2U;
                    constexpr std::uint32_t br          = 3U;
                    constexpr std::uint32_t spe         = 6U;
                    constexpr std::uint32_t lsbfirst    = 7U;
                    constexpr std::uint32_t ssi         = 8U;
                    constexpr std::uint32_t ssm         = 9U;
                    constexpr std::uint32_t rxonly      = 10U;
                    constexpr std::uint32_t dff         = 11U;
                    constexpr std::uint32_t crcnext     = 12U;
                    constexpr std::uint32_t crcen       = 13U;
                    constexpr std::uint32_t bidioe      = 14U;
                    constexpr std::uint32_t bidimode    = 15U;
                }

                namespace sr
                {
                    constexpr std::uint32_t rxne        = 0U;
                    constexpr std::uint32_t txe         = 1U;
                    constexpr std::uint32_t chside      = 2U;
                    constexpr std::uint32_t udr         = 3U;
                    constexpr std::uint32_t crcerr      = 4U;
                    constexpr std::uint32_t modf        = 5U;
                    constexpr std::uint32_t ovr         = 6U;
                    constexpr std::uint32_t bsy         = 7U;
                    constexpr std::uint32_t fre         = 8U;
                }
            } // namespace bitpos

            namespace mask
            {
                namespace cr1
                {
                    constexpr std::uint32_t cpha        = (1U << bitpos::cr1::cpha);
                    constexpr std::uint32_t cpol        = (1U << bitpos::cr1::cpol);
                    constexpr std::uint32_t mstr        = (1U << bitpos::cr1::mstr);
                    constexpr std::uint32_t br          = (7U << bitpos::cr1::br);
                    constexpr std::uint32_t spe         = (1U << bitpos::cr1::spe);
                    constexpr std::uint32_t lsbfirst    = (1U << bitpos::cr1::lsbfirst);
                    constexpr std::uint32_t ssi         = (1U << bitpos::cr1::ssi);
                    constexpr std::uint32_t ssm         = (1U << bitpos::cr1::ssm);
                    constexpr std::uint32_t rxonly      = (1U << bitpos::cr1::rxonly);
                    constexpr std::uint32_t dff         = (1U << bitpos::cr1::dff);
                    constexpr std::uint32_t crcnext     = (1U << bitpos::cr1::crcnext);
                    constexpr std::uint32_t crcen       = (1U << bitpos::cr1::crcen);
                    constexpr std::uint32_t bidioe      = (1U << bitpos::cr1::bidioe);
                    constexpr std::uint32_t bidimode    = (1U << bitpos::cr1::bidimode);
                }

                namespace sr
                {
                    constexpr std::uint32_t rxne        = (1U << bitpos::sr::rxne);
                    constexpr std::uint32_t txe         = (1U << bitpos::sr::txe);
                    constexpr std::uint32_t chside      = (1U << bitpos::sr::chside);
                    constexpr std::uint32_t udr         = (1U << bitpos::sr::udr);
                    constexpr std::uint32_t crcerr      = (1U << bitpos::sr::crcerr);
                    constexpr std::uint32_t modf        = (1U << bitpos::sr::modf);
                    constexpr std::uint32_t ovr         = (1U << bitpos::sr::ovr);
                    constexpr std::uint32_t bsy         = (1U << bitpos::sr::bsy);
                    constexpr std::uint32_t fre         = (1U << bitpos::sr::fre);
                }
            } // namespace bitpos
        } // namespace spi

        namespace i2c
        {
            namespace offset
            {
                constexpr std::uint32_t cr1        = 0x00;
                constexpr std::uint32_t cr2        = 0x04;
                constexpr std::uint32_t oar1       = 0x08;
                constexpr std::uint32_t oar2       = 0x0C;
                constexpr std::uint32_t dr         = 0x10;
                constexpr std::uint32_t sr1        = 0x14;
                constexpr std::uint32_t sr2        = 0x18;
                constexpr std::uint32_t ccr        = 0x1C;
                constexpr std::uint32_t trise      = 0x20;
            } // namespace offset

            namespace bitpos
            {
                 namespace cr1
                {
                    constexpr std::uint32_t pe          = 0U;
                    constexpr std::uint32_t smbus       = 1U;
                    constexpr std::uint32_t smbtype     = 3U;
                    constexpr std::uint32_t enarp       = 4U;
                    constexpr std::uint32_t enpec       = 5U;
                    constexpr std::uint32_t engc        = 6U;
                    constexpr std::uint32_t nostretch   = 7U;
                    constexpr std::uint32_t start       = 8U;
                    constexpr std::uint32_t stop        = 9U;
                    constexpr std::uint32_t ack         = 10U;
                    constexpr std::uint32_t pos         = 11U;
                    constexpr std::uint32_t pec         = 12U;
                    constexpr std::uint32_t alert       = 13U;
                    constexpr std::uint32_t swrst       = 15U;
                }

                namespace sr1
                {
                    constexpr std::uint32_t sb          = 0U;
                    constexpr std::uint32_t addr        = 1U;
                    constexpr std::uint32_t btf         = 2U;
                    constexpr std::uint32_t add10       = 3U;
                    constexpr std::uint32_t stopf       = 4U;
                    constexpr std::uint32_t rxne        = 6U;
                    constexpr std::uint32_t txe         = 7U;
                    constexpr std::uint32_t berr        = 8U;
                    constexpr std::uint32_t arlo        = 9U;
                    constexpr std::uint32_t af          = 10U;
                    constexpr std::uint32_t ovr         = 11U;
                    constexpr std::uint32_t pec         = 12U;
                    constexpr std::uint32_t timeout     = 14U;
                    constexpr std::uint32_t smbalert    = 15U;
                }
            }

            namespace mask
            {
                 namespace cr1
                {
                    constexpr std::uint32_t pe          = (1U << bitpos::cr1::pe);
                    constexpr std::uint32_t smbus       = (1U << bitpos::cr1::smbus);
                    constexpr std::uint32_t smbtype     = (1U << bitpos::cr1::smbtype);
                    constexpr std::uint32_t enarp       = (1U << bitpos::cr1::enarp);
                    constexpr std::uint32_t enpec       = (1U << bitpos::cr1::enpec);
                    constexpr std::uint32_t engc        = (1U << bitpos::cr1::engc);
                    constexpr std::uint32_t nostretch   = (1U << bitpos::cr1::nostretch);
                    constexpr std::uint32_t start       = (1U << bitpos::cr1::start);
                    constexpr std::uint32_t stop        = (1U << bitpos::cr1::stop);
                    constexpr std::uint32_t ack         = (1U << bitpos::cr1::ack);
                    constexpr std::uint32_t pos         = (1U << bitpos::cr1::pos);
                    constexpr std::uint32_t pec         = (1U << bitpos::cr1::pec);
                    constexpr std::uint32_t alert       = (1U << bitpos::cr1::alert);
                    constexpr std::uint32_t swrst       = (1U << bitpos::cr1::swrst);
                }

                namespace sr1
                {
                    constexpr std::uint32_t sb          = (1U << bitpos::sr1::sb);
                    constexpr std::uint32_t addr        = (1U << bitpos::sr1::addr);
                    constexpr std::uint32_t btf         = (1u << bitpos::sr1::btf);
                    constexpr std::uint32_t add10       = (1U << bitpos::sr1::add10);
                    constexpr std::uint32_t stopf       = (1U << bitpos::sr1::stopf);
                    constexpr std::uint32_t rxne        = (1U << bitpos::sr1::rxne);
                    constexpr std::uint32_t txe         = (1U << bitpos::sr1::txe);
                    constexpr std::uint32_t berr        = (1U << bitpos::sr1::berr);
                    constexpr std::uint32_t arlo        = (1U << bitpos::sr1::arlo);
                    constexpr std::uint32_t af          = (1U << bitpos::sr1::af);
                    constexpr std::uint32_t ovr         = (1U << bitpos::sr1::ovr);
                    constexpr std::uint32_t pec         = (1U << bitpos::sr1::pec);
                    constexpr std::uint32_t timeout     = (1U << bitpos::sr1::timeout);
                    constexpr std::uint32_t smbalert    = (1U << bitpos::sr1::smbalert);
                }
            }
        } // namespace i2c

    } // reg
} // mcal

#endif /* INC_MCAL_REG_HPP */