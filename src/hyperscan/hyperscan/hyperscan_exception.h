#pragma once

namespace Hyperscan {
    namespace Core {
        namespace Exceptions {
            [System::Serializable]
            public ref class HyperscanException : public System::Exception {
            public:
                HyperscanException() : System::Exception() {}
                HyperscanException(System::String^ message) : System::Exception(message) {}
                HyperscanException(System::String^ message, System::Exception^ inner) : System::Exception(message, inner) {}
            protected:
                HyperscanException(System::Runtime::Serialization::SerializationInfo^ info, System::Runtime::Serialization::StreamingContext context) : System::Exception(info, context) {}
            };
        }
    }
}