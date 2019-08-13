#pragma once

#include "base.h"

extern "C"
{
namespace winsdk
{
    // Forward declarations
    struct wsa_buf;
    struct quality_of_service;

    // Type definitions
    using socket_t = std::uintptr_t;

    using condition_proc = std::int32_t(__stdcall*)(
        wsa_buf* callerId,
        wsa_buf* callerData,
        quality_of_service* sQOS,
        quality_of_service* gQOS,
        wsa_buf* calleeId,
        wsa_buf* calleeData,
        std::uint32_t* group,
        std::uint32_t callbackData);

    using wsaoverlapped_completion_routine = void(__stdcall*)(
        std::uint32_t error,
        std::uint32_t transferred,
        overlapped* overlapped,
        std::uint32_t flags);

    // Constants
    constexpr socket_t invalid_socket = ~static_cast<std::uintptr_t>(0);

    constexpr std::int32_t socket_error = -1;

    constexpr std::size_t wsa_description_length = 256;
    constexpr std::size_t wsa_system_status_length = 128;
    constexpr std::size_t fd_setsize = 64;
    constexpr std::size_t wsaprotocol_len = 255;
    constexpr std::size_t max_protocol_chain = 7;
    constexpr std::size_t fd_max_events = 10;
    constexpr std::size_t inet_addrstrlen = 22;

    constexpr std::int32_t af_unspec = 0;
    constexpr std::int32_t af_unix = 1;
    constexpr std::int32_t af_inet = 2;
    constexpr std::int32_t af_implink = 3;
    constexpr std::int32_t af_pup = 4;
    constexpr std::int32_t af_chaos = 5;
    constexpr std::int32_t af_ipx = 6;
    constexpr std::int32_t af_ns = 6;
    constexpr std::int32_t af_iso = 7;
    constexpr std::int32_t af_osi = af_iso;
    constexpr std::int32_t af_ecma = 8;
    constexpr std::int32_t af_datakit = 9;
    constexpr std::int32_t af_ccitt = 10;
    constexpr std::int32_t af_sna = 11;
    constexpr std::int32_t af_decnet = 12;
    constexpr std::int32_t af_dli = 13;
    constexpr std::int32_t af_lat = 14;
    constexpr std::int32_t af_hylink = 15;
    constexpr std::int32_t af_appletalk = 16;
    constexpr std::int32_t af_netbios = 17;
    constexpr std::int32_t af_voiceview = 18;
    constexpr std::int32_t af_firefox = 19;
    constexpr std::int32_t af_unknown1 = 20;
    constexpr std::int32_t af_ban = 21;
    constexpr std::int32_t af_max = 22;

    constexpr std::int32_t sock_stream = 1;
    constexpr std::int32_t sock_dgram = 2;
    constexpr std::int32_t sock_raw = 3;
    constexpr std::int32_t sock_rdm = 4;
    constexpr std::int32_t sock_seqpacket = 5;

    constexpr std::int32_t ipproto_ip = 0;
    constexpr std::int32_t ipproto_icmp = 1;
    constexpr std::int32_t ipproto_igmp = 2;
    constexpr std::int32_t ipproto_ggp = 3;
    constexpr std::int32_t ipproto_tcp = 6;
    constexpr std::int32_t ipproto_pup = 12;
    constexpr std::int32_t ipproto_udp = 17;
    constexpr std::int32_t ipproto_idp = 22;
    constexpr std::int32_t ipproto_nd = 77;
    constexpr std::int32_t ipproto_raw = 255;
    constexpr std::int32_t ipproto_max = 256;

    constexpr std::uint32_t inaddr_any = 0x00000000;
    constexpr std::uint32_t inaddr_loopback = 0X7F000001;
    constexpr std::uint32_t inaddr_broadcast = 0XFFFFFFFF;
    constexpr std::uint32_t inaddr_none = 0XFFFFFFFF;

    constexpr std::uint32_t sd_receive = 0;
    constexpr std::uint32_t sd_send = 1;
    constexpr std::uint32_t sd_both = 2;

    // Structures
    struct wsa_data
    {
        std::uint16_t version;
        std::uint16_t high_version;
#ifdef _WIN64
        std::uint16_t max_sockets;
        std::uint16_t max_udp_dg;
        char* vendor_info;
        char description[wsa_description_length + 1];
        char system_status[wsa_system_status_length + 1];
#else
        char description[wsa_description_length + 1];
        char system_status[wsa_system_status_length + 1];
        std::uint16_t max_sockets;
        std::uint16_t max_udp_dg;
        char* vendor_info;
#endif
    };

    struct sockaddr
    {
        std::uint16_t sa_family;
        char sa_data[14];
    };

    struct in_addr
    {
        union
        {
            struct { std::uint8_t network, host, logical_host, impno; } bytes;
            struct { std::uint16_t network, host; } words;
            std::uint32_t addr;
        } data;
    };

    struct sockaddr_in
    {
        std::uint16_t family;
        std::uint16_t port;
        in_addr addr;
        char zero[8];
    };

    struct fd_set
    {
        std::uint32_t count;
        socket_t array[fd_setsize];

        void set(socket_t socket)
        {
            std::uint32_t i = 0;
            for (; i < count; ++i)
            {
                if (array[i] == socket) break;
            }

            if ((i == count) && (count < fd_setsize))
            {
                array[i] = socket;
                ++count;
            }
        }

        bool is_set(socket_t socket)
        {
            for (std::uint32_t i = 0; i < count; ++i)
            {
                if (array[i] == socket) return true;
            }

            return false;
        }
    };

    struct timeval
    {
        std::int32_t sec;
        std::int32_t usec;
    };

    struct  hostent
    {
        char* name;
        char** aliases;
        std::int16_t address_type;
        std::int16_t length;
        char** address_list;
    };

    struct  servent
    {
        char* name;
        char** aliases;
#ifdef _WIN64
        char* protocol;
        std::int16_t port;
#else
        std::int16_t port;
        char* protocol;
#endif
    };

    struct  protoent
    {
        char* name;
        char** aliases;
        std::int16_t proto;
    };

    struct wsa_buf
    {
        std::uint32_t length;
        char* buffer;
    };

    struct flowspec
    {
        std::uint32_t token_rate;
        std::uint32_t token_bucket_size;
        std::uint32_t peak_bandwidth;
        std::uint32_t latency;
        std::uint32_t delay_variation;
        std::uint32_t service_type;
        std::uint32_t max_sdu_size;
        std::uint32_t minimum_policed_size;
    };

    struct quality_of_service
    {
        flowspec sending_flowspec;
        flowspec receiving_flowspec;
        wsa_buf provider_specific;
    };

    struct socket_address
    {
        sockaddr* sockaddr;
        std::int32_t sockaddr_length;
    };

    struct socket_address_list
    {
        std::int32_t address_count;
        socket_address address[1];
    };

    struct wsa_protocol_chain
    {
        std::int32_t chain_length;
        std::uint32_t chain_entries[max_protocol_chain];
    };

    struct wsa_protocol_infoa
    {
        std::uint32_t service_flags1;
        std::uint32_t service_flags2;
        std::uint32_t service_flags3;
        std::uint32_t service_flags4;
        std::uint32_t provider_flags;
        guid provider_id;
        std::uint32_t catalog_entry_id;
        wsa_protocol_chain protocol_chain;
        std::int32_t version;
        std::int32_t address_family;
        std::int32_t max_sock_addr;
        std::int32_t min_sock_addr;
        std::int32_t socket_type;
        std::int32_t protocol;
        std::int32_t protocol_max_offset;
        std::int32_t network_byte_order;
        std::int32_t security_scheme;
        std::uint32_t message_size;
        std::uint32_t provider_reserved;
        char protocol_name[wsaprotocol_len + 1];
    };

    struct wsa_protocol_infow
    {
        std::uint32_t service_flags1;
        std::uint32_t service_flags2;
        std::uint32_t service_flags3;
        std::uint32_t service_flags4;
        std::uint32_t provider_flags;
        guid provider_id;
        std::uint32_t catalog_entry_id;
        wsa_protocol_chain protocol_chain;
        std::int32_t version;
        std::int32_t address_family;
        std::int32_t max_sock_addr;
        std::int32_t min_sock_addr;
        std::int32_t socket_type;
        std::int32_t protocol;
        std::int32_t protocol_max_offset;
        std::int32_t network_byte_order;
        std::int32_t security_scheme;
        std::uint32_t message_size;
        std::uint32_t provider_reserved;
        wchar_t protocol_name[wsaprotocol_len + 1];
    };

    struct wsa_network_events
    {
        std::int32_t network_events;
        std::int32_t error_code[fd_max_events];
    };

    struct wsa_msg
    {
        sockaddr* name;
        std::int32_t name_length;
        wsa_buf* buffers;
        std::uint32_t buffer_count;
        wsa_buf control;
        std::uint32_t flags;
    };

    enum class wsa_comparator
    {
        equal = 0,
        not_less
    };

    struct wsa_version
    {
        std::uint32_t version;
        wsa_comparator how;
    };

    struct af_protocols
    {
        std::int32_t address_family;
        std::int32_t protocol;
    };

    struct csaddr_info
    {
        socket_address local_addr;
        socket_address remote_addr;
        std::int32_t socket_type;
        std::int32_t protocol;
    };

    struct blob
    {
        std::uint32_t size;
        std::uint8_t* blob_data;
    };

    struct wsa_query_seta
    {
        std::uint32_t size;
        char* service_instance_name;
        guid* service_class_id;
        wsa_version* version;
        char* comment;
        std::uint32_t name_space;
        guid* provider_id;
        char* context;
        std::uint32_t number_of_protocols;
        af_protocols* protocols;
        char* query_string;
        std::uint32_t number_of_cs_addrs;
        csaddr_info* buffer;
        std::uint32_t output_flags;
        blob* blob;
    };

    struct wsa_query_setw
    {
        std::uint32_t size;
        wchar_t* service_instance_name;
        guid* service_class_id;
        wsa_version* version;
        wchar_t* comment;
        std::uint32_t name_space;
        guid* provider_id;
        wchar_t* context;
        std::uint32_t number_of_protocols;
        af_protocols* protocols;
        wchar_t* query_string;
        std::uint32_t number_of_cs_addrs;
        csaddr_info* buffer;
        std::uint32_t output_flags;
        blob* blob;
    };

    enum class wsa_completion_type
    {
        notify_immediately = 0,
        notify_hwnd,
        notify_event,
        notify_port,
        notify_apc,
    };

    struct wsa_completion
    {
        wsa_completion_type type;
        union
        {
            struct
            {
                hwnd_t hwnd;
                std::uint32_t msg;
                std::uintptr_t context;
            } window_message;
            struct
            {
                overlapped* overlapped;
            } event;
            struct
            {
                overlapped* overlapped;
                wsaoverlapped_completion_routine completion_proc;
            } apc;
            struct
            {
                overlapped* overlapped;
                handle_t port;
                std::uintptr_t key;
            } port;
        } parameters;
    };

    struct wsan_class_infoa
    {
        char* name;
        std::uint32_t name_space;
        std::uint32_t value_type;
        std::uint32_t value_size;
        void* value;
    };

    struct wsan_class_infow
    {
        wchar_t* name;
        std::uint32_t name_space;
        std::uint32_t value_type;
        std::uint32_t value_size;
        void* value;
    };

    struct wsa_service_class_infoa
    {
        guid* service_class_id;
        char* service_class_name;
        std::uint32_t count;
        wsan_class_infoa* class_infos;
    };

    struct wsa_service_class_infow
    {
        guid* service_class_id;
        wchar_t* service_class_name;
        std::uint32_t count;
        wsan_class_infow* class_infos;
    };

    struct wsa_namespace_infoa
    {
        guid provider_id;
        std::uint32_t name_space;
        bool_t active;
        std::uint32_t version;
        char* identifier;
    };

    struct wsa_namespace_infow
    {
        guid provider_id;
        std::uint32_t name_space;
        bool_t active;
        std::uint32_t version;
        wchar_t* identifier;
    };

    struct wsa_namespace_info_exa
    {
        guid provider_id;
        std::uint32_t name_space;
        bool_t active;
        std::uint32_t version;
        char* identifier;
        blob provider_specific;
    };

    struct wsa_namespace_info_exw
    {
        guid provider_id;
        std::uint32_t name_space;
        bool_t active;
        std::uint32_t version;
        wchar_t* identifier;
        blob provider_specific;
    };

    enum class wsa_set_service_op
    {
        register_service = 0,
        deregister_service,
        delete_service,
    };

    struct pollfd
    {
        socket_t fd;
        std::int16_t events;
        std::int16_t revents;
    };

    // Berkley Functions
    __declspec(dllimport)
    socket_t __stdcall accept(socket_t socket, sockaddr* addr, std::int32_t* addrLen);

    __declspec(dllimport)
    std::int32_t __stdcall bind(socket_t socket, const sockaddr* name, std::int32_t nameLen);

    __declspec(dllimport)
    std::int32_t __stdcall closesocket(socket_t socket);

    __declspec(dllimport)
    std::int32_t __stdcall connect(socket_t socket, const sockaddr* name, std::int32_t nameLen);

    __declspec(dllimport)
    std::int32_t __stdcall ioctlsocket(socket_t socket, long cmd, std::uint32_t* arg);

    __declspec(dllimport)
    std::int32_t __stdcall getpeername(socket_t socket, sockaddr* name, std::int32_t* nameLen);

    __declspec(dllimport)
    std::int32_t __stdcall getsockname(socket_t socket, sockaddr* name, std::int32_t* nameLen);

    __declspec(dllimport)
    std::int32_t __stdcall getsockopt(
        socket_t socket,
        std::int32_t level,
        std::int32_t optname,
        char* optVal,
        std::int32_t* optLen);

    __declspec(dllimport)
    std::uint32_t __stdcall htonl(std::uint32_t hostLong);

    __declspec(dllimport)
    std::uint16_t __stdcall htons(std::uint16_t hostShort);

    __declspec(dllimport)
    unsigned long __stdcall inet_addr(const char* address);

    __declspec(dllimport)
    char* __stdcall inet_ntoa(in_addr address);

    __declspec(dllimport)
    std::int32_t __stdcall inet_pton(std::int32_t family, const char* addrString, void* addrBuffer);

    std::int32_t __stdcall InetPtonW(std::int32_t family, const wchar_t* addrString, void* addrBufuffer);

    const char* __stdcall inet_ntop(std::int32_t family, const void* addr, char* buffer, std::size_t bufferSize);

    const wchar_t* __stdcall InetNtopW(std::int32_t family, const void* addr, wchar_t* buffer, std::size_t bufferSize);

    inline std::uint64_t htonll(std::uint64_t value)
    {
        return ((value >> 56) & 0x00000000000000FFll) |
            ((value >> 40) & 0x000000000000FF00ll) |
            ((value >> 24) & 0x0000000000FF0000ll) |
            ((value >>  8) & 0x00000000FF000000ll) |
            ((value <<  8) & 0x000000FF00000000ll) |
            ((value << 24) & 0x0000FF0000000000ll) |
            ((value << 40) & 0x00FF000000000000ll) |
            ((value << 56) & 0xFF00000000000000ll);
    }

    inline std::uint64_t ntohll(std::uint64_t value)
    {
        return htonll(value);
    }

    inline std::uint32_t htonf(float value)
    {
        auto& temp = *reinterpret_cast<std::uint32_t*>(&value);
        return ((temp >> 24) & 0x000000FF) |
            ((temp >>  8) & 0x0000FF00) |
            ((temp <<  8) & 0x00FF0000) |
            ((temp << 24) & 0xFF000000);
    }

    inline float ntohf(std::uint32_t value)
    {
        auto result = ((value >> 24) & 0x000000FF) |
            ((value >>  8) & 0x0000FF00) |
            ((value <<  8) & 0x00FF0000) |
            ((value << 24) & 0xFF000000);
        return *reinterpret_cast<float*>(&result);
    }

    inline std::uint64_t htond(double value)
    {
        return htonll(*reinterpret_cast<std::uint64_t*>(&value));
    }

    inline double ntohd(std::uint64_t value)
    {
        auto temp = ntohll(value);
        return *reinterpret_cast<double*>(&temp);
    }

    __declspec(dllimport)
    std::int32_t __stdcall listen(socket_t socket, std::int32_t backlog);

    __declspec(dllimport)
    std::uint32_t __stdcall ntohl(std::uint32_t netLong);

    __declspec(dllimport)
    std::uint16_t __stdcall ntohs(std::uint16_t netShort);

    __declspec(dllimport)
    std::int32_t __stdcall recv(socket_t socket, char* buffer, std::int32_t bufferLen, std::int32_t flags);

    __declspec(dllimport)
    std::int32_t __stdcall recvfrom(
        socket_t socket,
        char* buffer,
        std::int32_t bufferLen,
        std::int32_t flags,
        sockaddr* from,
        std::int32_t* fromLen);

    __declspec(dllimport)
    std::int32_t __stdcall select(
        std::int32_t nfds,
        fd_set* read,
        fd_set* write,
        fd_set* except,
        const timeval* timeout);

    __declspec(dllimport)
    std::int32_t __stdcall send(socket_t socket, const char* buffer, std::int32_t bufferLen, std::int32_t flags);

    __declspec(dllimport)
    std::int32_t __stdcall sendto(socket_t socket,
        const char* buffer,
        std::int32_t bufferLen,
        std::int32_t flags,
        const sockaddr* to,
        std::int32_t tolen);

    __declspec(dllimport)
    std::int32_t __stdcall setsockopt(
        socket_t socket,
        std::int32_t level,
        std::int32_t optName,
        const char* optVal,
        std::int32_t optLen);

    __declspec(dllimport)
    std::int32_t __stdcall shutdown(socket_t socket, std::int32_t how);

    __declspec(dllimport)
    socket_t __stdcall socket(std::int32_t af, std::int32_t type, std::int32_t protocol);

    __declspec(dllimport)
    struct hostent* __stdcall gethostbyaddr(const char* addr, std::int32_t addrLen, std::int32_t type);

    __declspec(dllimport)
    struct hostent* __stdcall gethostbyname(const char* name);

    __declspec(dllimport)
    std::int32_t __stdcall gethostname(char* name, std::int32_t nameLen);

    __declspec(dllimport)
    std::int32_t __stdcall GetHostNameW(wchar_t* name, std::int32_t nameLen);

    __declspec(dllimport)
    struct servent* __stdcall getservbyport(std::int32_t port, const char* proto);

    __declspec(dllimport)
    struct servent* __stdcall getservbyname(const char* name, const char* proto);

    __declspec(dllimport)
    struct protoent* __stdcall getprotobynumber(std::int32_t number);

    __declspec(dllimport)
    struct protoent* __stdcall getprotobyname(const char* name);

    // WinSock Extension Functions
    __declspec(dllimport)
    std::int32_t __stdcall WSAStartup(std::uint16_t versionRequested, wsa_data* data);

    __declspec(dllimport)
    std::int32_t __stdcall WSACleanup();

    __declspec(dllimport)
    void __stdcall WSASetLastError(std::int32_t error);

    __declspec(dllimport)
    std::int32_t __stdcall WSAGetLastError();

    __declspec(dllimport)
    bool_t __stdcall WSAIsBlocking();

    __declspec(dllimport)
    std::int32_t __stdcall WSAUnhookBlockingHook();

    __declspec(dllimport)
    farproc __stdcall WSASetBlockingHook(farproc lpBlockFunc);

    __declspec(dllimport)
    std::int32_t __stdcall WSACancelBlockingCall();

    __declspec(dllimport)
    handle_t __stdcall WSAAsyncGetServByName(
        hwnd_t hwnd,
        std::uint32_t msg,
        const char* name,
        const char* proto,
        char* buffer,
        std::int32_t bufferLen);

    __declspec(dllimport)
    handle_t __stdcall WSAAsyncGetServByPort(
        hwnd_t hwnd,
        std::uint32_t msg,
        std::int32_t port,
        const char* proto,
        char* buffer,
        std::int32_t bufferLen);

    __declspec(dllimport)
    handle_t __stdcall WSAAsyncGetProtoByName(
        hwnd_t hwnd,
        std::uint32_t msg,
        const char* name,
        char* buffer,
        std::int32_t bufferLen);

    __declspec(dllimport)
    handle_t __stdcall WSAAsyncGetProtoByNumber(
        hwnd_t hwnd,
        std::uint32_t msg,
        std::int32_t number,
        char* buffer,
        std::int32_t bufferLen);

    __declspec(dllimport)
    handle_t __stdcall WSAAsyncGetHostByName(
        hwnd_t hwnd,
        std::uint32_t msg,
        const char* name,
        char* buffer,
        std::int32_t bufferLen);

    __declspec(dllimport)
    handle_t __stdcall WSAAsyncGetHostByAddr(
        hwnd_t hwnd,
        std::uint32_t msg,
        const char* addr,
        std::int32_t len,
        std::int32_t type,
        char* buffer,
        std::int32_t bufferLen);

    __declspec(dllimport)
    std::int32_t __stdcall WSACancelAsyncRequest(handle_t asyncTaskHandle);

    __declspec(dllimport)
    std::int32_t __stdcall WSAAsyncSelect(socket_t socket, hwnd_t hwnd, std::uint32_t msg, std::int32_t event);

    __declspec(dllimport)
    socket_t __stdcall WSAAccept(
        socket_t socket,
        sockaddr* addr,
        std::int32_t* addrLen,
        condition_proc condition,
        std::uint32_t callbackData);

    __declspec(dllimport)
    bool_t __stdcall WSACloseEvent(handle_t hEvent);

    __declspec(dllimport)
    std::int32_t __stdcall WSAConnect(
        socket_t socket,
        const sockaddr* name,
        std::int32_t nameLen,
        wsa_buf* callerData,
        wsa_buf* calleeData,
        quality_of_service* sQOS,
        quality_of_service* gQOS);

    bool_t __stdcall WSAConnectByNameW(
        socket_t socket,
        wchar_t* nodeName,
        wchar_t* serviceName,
        std::uint32_t* localAddressLength,
        sockaddr* localAddress,
        std::uint32_t* remoteAddressLength,
        sockaddr* remoteAddress,
        const timeval* timeout,
        overlapped* reserved);

    bool_t __stdcall WSAConnectByNameA(
        socket_t socket,
        const char* nodeName,
        const char* serviceName,
        std::uint32_t* localAddressLength,
        sockaddr* localAddress,
        std::uint32_t* remoteAddressLength,
        sockaddr* remoteAddress,
        const timeval* timeout,
        overlapped* reserved);

    bool_t __stdcall WSAConnectByList(
        socket_t socket,
        socket_address_list* socketAddress,
        std::uint32_t* localAddressLength,
        sockaddr* localAddress,
        std::uint32_t* remoteAddressLength,
        sockaddr* remoteAddress,
        const timeval* timeout,
        overlapped* reserved);

    __declspec(dllimport)
    handle_t __stdcall WSACreateEvent();

    __declspec(dllimport)
    std::int32_t __stdcall WSADuplicateSocketA(
        socket_t socket,
        std::uint32_t processId,
        wsa_protocol_infoa* protocolInfo);

    __declspec(dllimport)
    std::int32_t __stdcall WSADuplicateSocketW(
        socket_t socket,
        std::uint32_t processId,
        wsa_protocol_infow* protocolInfo);

    __declspec(dllimport)
    std::int32_t __stdcall WSAEnumNetworkEvents(socket_t socket, handle_t eventObject, wsa_network_events* networkEvents);

    __declspec(dllimport)
    std::int32_t __stdcall WSAEnumProtocolsA(
        std::int32_t* protocols,
        wsa_protocol_infoa* protocolBuffer,
        std::uint32_t* bufferLength);

    __declspec(dllimport)
    std::int32_t __stdcall WSAEnumProtocolsW(
        std::int32_t* protocols,
        wsa_protocol_infow* protocolBuffer,
        std::uint32_t* bufferLength);

    __declspec(dllimport)
    std::int32_t __stdcall WSAEventSelect(socket_t socket, handle_t eventObject, std::int32_t networkEvents);

    __declspec(dllimport)
    bool_t __stdcall WSAGetOverlappedResult(
        socket_t socket,
        overlapped* overlapped,
        std::uint32_t* transfer,
        bool_t wait,
        std::uint32_t* flags);

    __declspec(dllimport)
    bool_t __stdcall WSAGetQOSByName(socket_t socket, wsa_buf* qosName, quality_of_service* qos);

    __declspec(dllimport)
    std::int32_t __stdcall WSAHtonl(socket_t socket, std::uint32_t hostLong, std::uint32_t* netLong);

    __declspec(dllimport)
    std::int32_t __stdcall WSAHtons(socket_t socket, std::uint16_t hostShort, std::uint16_t* netShort);

    __declspec(dllimport)
    std::int32_t __stdcall WSAIoctl(
        socket_t socket,
        std::uint32_t ioControlCode,
        void* inBuffer,
        std::uint32_t inBufferSize,
        void* outBuffer,
        std::uint32_t outBufferSize,
        std::uint32_t* bytesReturned,
        overlapped* overlapped,
        wsaoverlapped_completion_routine completionRoutine);

    __declspec(dllimport)
    socket_t __stdcall WSAJoinLeaf(
        socket_t socket,
        const sockaddr* name,
        std::int32_t namelen,
        wsa_buf* callerData,
        wsa_buf* calleeData,
        quality_of_service* sQOS,
        quality_of_service* gQOS,
        std::uint32_t flags);

    __declspec(dllimport)
    std::int32_t __stdcall WSANtohl(socket_t socket, std::uint32_t netLong, std::uint32_t* hostLong);

    __declspec(dllimport)
    std::int32_t __stdcall WSANtohs(socket_t socket, std::uint16_t netShort, std::uint16_t* hostShort);

    __declspec(dllimport)
    std::int32_t __stdcall WSARecv(
        socket_t socket,
        wsa_buf* buffers,
        std::uint32_t bufferCount,
        std::uint32_t* numberOfBytesRecvd,
        std::uint32_t* flags,
        overlapped* overlapped,
        wsaoverlapped_completion_routine completionRoutine);

    __declspec(dllimport)
    std::int32_t __stdcall WSARecvDisconnect(socket_t socket, wsa_buf* inboundDisconnectData);

    __declspec(dllimport)
    std::int32_t __stdcall WSARecvFrom(
        socket_t socket,
        wsa_buf* buffers,
        std::uint32_t bufferCount,
        std::uint32_t* numberOfBytesRecvd,
        std::uint32_t* flags,
        sockaddr* from,
        std::int32_t* fromlen,
        overlapped* overlapped,
        wsaoverlapped_completion_routine completionRoutine);

    __declspec(dllimport)
    bool_t __stdcall WSAResetEvent(handle_t event);

    __declspec(dllimport)
    std::int32_t __stdcall WSASend(
        socket_t socket,
        wsa_buf* buffers,
        std::uint32_t bufferCount,
        std::uint32_t* numberOfBytesSent,
        std::uint32_t flags,
        overlapped* overlapped,
        wsaoverlapped_completion_routine completionRoutine);

    __declspec(dllimport)
    std::int32_t __stdcall WSASendMsg(
        socket_t handle,
        wsa_msg* msg,
        std::uint32_t flags,
        std::uint32_t* numberOfBytesSent,
        overlapped* overlapped,
        wsaoverlapped_completion_routine completionRoutine);

    __declspec(dllimport)
    std::int32_t __stdcall WSASendDisconnect(socket_t socket, wsa_buf* outboundDisconnectData);

    __declspec(dllimport)
    std::int32_t __stdcall WSASendTo(
        socket_t socket,
        wsa_buf* buffers,
        std::uint32_t bufferCount,
        std::uint32_t* numberOfBytesSent,
        std::uint32_t flags,
        const sockaddr* to,
        std::int32_t tolen,
        overlapped* overlapped,
        wsaoverlapped_completion_routine completionRoutine);

    __declspec(dllimport)
    bool_t __stdcall WSASetEvent(handle_t event);

    __declspec(dllimport)
    socket_t __stdcall WSASocketA(
        std::int32_t af,
        std::int32_t type,
        std::int32_t protocol,
        wsa_protocol_infoa* protocolInfo,
        std::uint32_t group,
        std::uint32_t flags);

    __declspec(dllimport)
    socket_t __stdcall WSASocketW(
        std::int32_t af,
        std::int32_t type,
        std::int32_t protocol,
        wsa_protocol_infow* protocolInfo,
        std::uint32_t group,
        std::uint32_t flags);

    __declspec(dllimport)
    std::uint32_t __stdcall WSAWaitForMultipleEvents(
        std::uint32_t eventCount,
        const handle_t* events,
        bool_t waitAll,
        std::uint32_t timeout,
        bool_t alertable);

    __declspec(dllimport)
    std::int32_t __stdcall WSAAddressToStringA(
        sockaddr* address,
        std::uint32_t addressLength,
        wsa_protocol_infoa* protocolInfo,
        char* addressString,
        std::uint32_t* addressStringLength);

    __declspec(dllimport)
    std::int32_t __stdcall WSAAddressToStringW(
        sockaddr* address,
        std::uint32_t addressLength,
        wsa_protocol_infow* protocolInfo,
        wchar_t* addressString,
        std::uint32_t* addressStringLength);

    __declspec(dllimport)
    std::int32_t __stdcall WSAStringToAddressA(
        char* addressString,
        std::int32_t addressFamily,
        wsa_protocol_infoa* protocolInfo,
        sockaddr* address,
        std::int32_t* addressLength);

    __declspec(dllimport)
    std::int32_t __stdcall WSAStringToAddressW(
        wchar_t* addressString,
        std::int32_t addressFamily,
        wsa_protocol_infow* protocolInfo,
        sockaddr* address,
        std::int32_t* addressLength);

    __declspec(dllimport)
    std::int32_t __stdcall WSALookupServiceBeginA(
        wsa_query_seta* restrictions,
        std::uint32_t controlFlags,
        handle_t* lookup);

    __declspec(dllimport)
    std::int32_t __stdcall WSALookupServiceBeginW(
        wsa_query_setw* restrictions,
        std::uint32_t controlFlags,
        handle_t* lookup);

    __declspec(dllimport)
    std::int32_t __stdcall WSALookupServiceNextA(
        handle_t lookup,
        std::uint32_t controlFlags,
        std::uint32_t* bufferLength,
        wsa_query_seta* results);

    __declspec(dllimport)
    std::int32_t __stdcall WSALookupServiceNextW(
        handle_t lookup,
        std::uint32_t controlFlags,
        std::uint32_t* bufferLength,
        wsa_query_setw* results);

    __declspec(dllimport)
    std::int32_t __stdcall WSANSPIoctl(
        handle_t lookup,
        std::uint32_t controlCode,
        void* inBuffer,
        std::uint32_t inBufferSize,
        void* outBuffer,
        std::uint32_t outBufferSize,
        std::uint32_t* bytesReturned,
        wsa_completion* completion);

    __declspec(dllimport)
    std::int32_t __stdcall WSALookupServiceEnd(handle_t lookup);

    __declspec(dllimport)
    std::int32_t __stdcall WSAInstallServiceClassA(wsa_service_class_infoa* serviceClassInfo);

    __declspec(dllimport)
    std::int32_t __stdcall WSAInstallServiceClassW(wsa_service_class_infow* serviceClassInfo);

    __declspec(dllimport)
    std::int32_t __stdcall WSARemoveServiceClass(guid* serviceClassId);

    __declspec(dllimport)
    std::int32_t __stdcall WSAGetServiceClassInfoA(
        guid* providerId,
        guid* serviceClassId,
        std::uint32_t* bufSize,
        wsa_service_class_infoa* serviceClassInfo);

    __declspec(dllimport)
    std::int32_t __stdcall WSAGetServiceClassInfoW(
        guid* providerId,
        guid* serviceClassId,
        std::uint32_t* bufSize,
        wsa_service_class_infow* serviceClassInfo);

    __declspec(dllimport)
    std::int32_t __stdcall WSAEnumNameSpaceProvidersA(std::uint32_t* bufferLength, wsa_namespace_infoa* buffer);

    __declspec(dllimport)
    std::int32_t __stdcall WSAEnumNameSpaceProvidersW(std::uint32_t* bufferLength, wsa_namespace_infow* buffer);

    __declspec(dllimport)
    std::int32_t __stdcall WSAEnumNameSpaceProvidersExA(std::uint32_t* bufferLength, wsa_namespace_info_exa* buffer);

    __declspec(dllimport)
    std::int32_t __stdcall WSAEnumNameSpaceProvidersExW(std::uint32_t* bufferLength, wsa_namespace_info_exw* buffer);

    __declspec(dllimport)
    std::int32_t __stdcall WSAGetServiceClassNameByClassIdA(
        guid* serviceClassId,
        char* serviceClassName,
        std::uint32_t* bufferLength);

    __declspec(dllimport)
    std::int32_t __stdcall WSAGetServiceClassNameByClassIdW(
        guid* serviceClassId,
        wchar_t* serviceClassName,
        std::uint32_t* bufferLength);

    __declspec(dllimport)
    std::int32_t __stdcall WSASetServiceA(
        wsa_query_seta* regInfo,
        wsa_set_service_op operation,
        std::uint32_t controlFlags);

    __declspec(dllimport)
    std::int32_t __stdcall WSASetServiceW(
        wsa_query_setw* regInfo,
        wsa_set_service_op operation,
        std::uint32_t controlFlags);

    __declspec(dllimport)
    std::int32_t __stdcall WSAProviderConfigChange(
        handle_t* notificationHandle,
        overlapped* overlapped,
        wsaoverlapped_completion_routine completionRoutine);

    __declspec(dllimport)
    std::int32_t __stdcall WSAPoll(
        pollfd* array,
        std::uint32_t fds,
        std::int32_t timeout);
}
}
