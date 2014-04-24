#pragma once

namespace rh {

    typedef unsigned int ComponentGroupId;

    /**
     * Base class exists to track group counter
     */
    class BaseComponent
    {
        public:
            BaseComponent() {};
            virtual ~BaseComponent() {};
        protected:
            static ComponentGroupId group_id_counter_;
    };


    /**
     * New components should extend this class
     */
    template <typename T>
    class Component : public BaseComponent
    {
        public:
            static  ComponentGroupId get_group_id();
        private:
            // Group ID for components of type T
            static ComponentGroupId group_id;

    };

    template <typename T>
    ComponentGroupId Component<T>::get_group_id() {
        static ComponentGroupId group_id = group_id_counter_++;
        return group_id;
    }

}
