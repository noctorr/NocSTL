#include <functional>

namespace stl {

    template < typename _Type >
    class function;

    template < typename _Ret, typename... _Args >
    class function<_Ret(_Args...)> final
    {
        public:
        using type = _Ret(_Args...);
        private:
        type* self;

        public:
        function() = default;
        
        function(
            type& func
        ) {
            self = func;
        }
        function(
            const function& other
        ) : self(other.self) {}

        function(
            function&& other
        ) : self(other.self) {
            other.self = nullptr;
        }

        ~function() = default;

        function& operator= (const function& other) {
            if ( this != &other ) { 
                self = other.self;
            }

            return *this;
        }

        function& operator= ( function&& other ) {
            if ( this != &other ) {
                self = other.self;
                other.self = nullptr;
            }

            return *this;
        }

        void set(type& funct) {
            self = funct;
        }

        _Ret operator() ( _Args... Params ) {
            return std::invoke(self, Params...);
        }
    };
}
