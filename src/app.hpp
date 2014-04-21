#pragma once

#include <SFML/Graphics.hpp>

namespace RH {

    class Application {
        public:
            virtual             ~Application() {}
            virtual void        init(const std::string title, unsigned int width, unsigned int height, unsigned int depth, bool fullscreen);
            virtual void        run();
            static Application *get_instance();

        protected:
            Application() {};
        private:
            static  std::unique_ptr<Application> instance_;
            sf::RenderWindow    *window_;
    };

}
