# Staxys Directory Structure Documentation

THIS IS A WORK IN PROGRESS

This document provides an overview of the Staxys project, including the purpose of
each directory and its contents. This structure is designed to separate configuration
files, logs, static content, and other resources for ease of use and maintainability.

#### Table of Contents

- [Overview](#Overview)
- [License](#License)
- [/etc/staxys/](#etcstaxys-main-configuration-directory)
    - [/etc/staxys/conf.d/](#etcstaxysconfd)
    - [/etc/staxys/ssl/](#etcstaxysssl)
- [/var/log/staxys/](#varlogstaxys-log-files)
    - [/var/log/staxys/access.log](#varlogstaxysaccesslog)
    - [/var/log/staxys/error.log](#varlogstaxyserrorlog)
- [/var/www/](#varwww-web-root-directory)
- [/usr/local/staxys/html](#usrlocalstaxyshtml-static-content-directory-for-source-installation)
    - [/usr/local/staxys/html/staxys.css](#usrlocalstaxyshtmlstaxyscss)
    - [/usr/local/staxys/html/index.html](#usrlocalstaxyshtmlindexhtml)
    - [/usr/local/staxys/html/staxys.js](#usrlocalstaxyshtmlstaxysjs)

#### Overview

```
/etc/staxys/                # Main configuration directory
    ├── staxys.cfg          # Main Staxys configuration file
    ├── conf.d/             # Additional config files
    │   ├── server1.cfg     # Example site config
    │   ├── server2.cfg     # Example site config
    │   ├── server3.cfg     # Example site config
    │   ├── server4.cfg     # Example site config
    │   └── server5.cfg     # Example site config
    └── ssl/                # Directory for SSL certificates
        ├── server.crt      # SSL certificate
        └── server.key      # SSL private key

/var/log/staxys/            # Log files
    ├── access.log          # Access log
    └── error.log           # Error log

/var/www/                   # Web root directory
    └── html/               # Default static content directory
        ├── index.html      # Default HTML file
        ├── staxys.css      # Default CSS
        └── staxys.js       # Default JS

/usr/local/staxys/          # Source installation (if applicable)
    └── staxys              # The Staxys executable (main service manager)

/usr/local/staxys/html/     # Default static content directory for source
    ├── staxys.css          # Default CSS
    ├── index.html          # Default HTML
    └── staxys.js           # Default JS
```

#### License

- This project is released under the Apache 2.0 license. For more information, see
  the [LICENSE](LICENSE) file.

#### /etc/staxys/ (Main Configuration Directory)

- This is the main directory for all Staxys configuration files. It contains
  the primary configuration file (staxys.conf) and additional configurations
  located in the conf.d/ directory. It also includes a directory for SSL
  certificates.

- `staxys.conf`: The main configuration file for Staxys. This file contains global
  settings and configuration options for the service manager. It handles global
  configurations such as the ports to listen on, logging setup, SSL/TLS settings,
  caching, and other server-wide options. This file is essential for setting up the
  overall behavior of the Staxys service. Further configuration can be found in the
  [Global Configuration](#global-configuration) section.

##### /etc/staxys/conf.d/:

- A directory that holds additional configuration files. Each file in this directory
  defines specific site or service settings (e.g., server, routes). These
  files can be modularized for better management. Example files include `server1.cfg`,
  `server2.cfg`, etc. Further configuration can be found in
  the [Server Configuration](#server-configuration) section.

##### /etc/staxys/ssl/:

- A directory that contains SSL certificates and private keys. These are used for
  securing communications with the Staxys service. Example files include `server.crt`
  and `server.key`.

#### /var/log/staxys/ (Log Files)

- This directory stores all logs generated by Staxys, including access logs and error
  logs.

##### /var/log/staxys/access.log:

- Logs of incoming requests to Staxys, including details like request method, URL,
  IP address, and response status. This file is helpful for tracking and analyzing
  traffic. An example of the access log is the following:

```
192.168.1.1 - [12/Jan/2025:10:00:00 +0000] "GET /index.html HTTP/1.1" 200 1024 "https://example.com/" "Chrome/91.0.4472.124"
```

- IP: 192.168.1.1 (client IP address)
- User: - no user authenticated (if a user is authenticated, it will be shown here)
- Timestamp: [12/Jan/2025:10:00:00 +0000]
- Request: "GET /index.html HTTP/1.1"
- Status Code: 200 (successful request)
- Response Size: 1024 (bytes sent in the response body)
- Referer: "http://example.com/" (referring URL)
- User-Agent: "Chrome/91.0.4472.124"

- The default log format is the following.

```
log_format = "%h %u %t \"%r\" %>s %b \"%{Referer}i\" \"%{User-Agent}i\""
- %h: The client's IP address.
- %u: The authenticated user. If no user is authenticated, this will be -.
- %t: The timestamp of the request.
- %r: The request line (method, path, HTTP version).
- %>s: The status code returned by the server.
- %b: The size of the response body.
- %{Referer}i: The Referer HTTP header.
- %{User-Agent}i: The User-Agent HTTP header.
```

##### /var/log/staxys/error.log:

- Logs of errors encountered by the Staxys service, such as misconfigurations, server
  issues, or failures during request processing. An example of the access log is the following:

```
[12/Jan/2025:10:00:00 +0000] 12345 "GET "/nonexistent-page" 404 2048 "https://example.com/" "Chrome/91.0.4472.124"
```

- Timestamp: [12/Jan/2025:10:00:00 +0000] (When the error occurred)
- Process ID: 12345 (The process ID handling this error)
- Request: "GET /nonexistent-page HTTP/1.1" (The request line for the error-causing request)
- HTTP Method: GET (The method used)
- Requested URL: /nonexistent-page (The path that caused the error)
- Status Code: 404 (The error code indicating that the page was not found)
- Response Size: 2048 (The size of the response body, even if it’s an error page)
- Referer: "http://example.com/" (The page that the request came from)
- User-Agent: "Chrome/91.0.4472.124" (The client that made the request)

- The default log format is the following.

```
log_format = "%t %p %r %m %U %s %b \"%{Referer}i\" \"%{User-Agent}i\""
- %t: The timestamp when the error occurred, formatted as [dd/Mon/yyyy:hh:mm:ss +zzzz]. 
      This is essential for logging when an error happened.
- %p: The process ID (PID) of the server process handling the request. This can be useful 
      for identifying which server instance caused the error in a multi-process environment.
- %r: The request line from the client that caused the error (e.g., "GET /index.html HTTP/1.1"). 
      This gives context about the request that led to the error.
- %m: The HTTP method (e.g., GET, POST) used in the request.
- %U: The URL or path that was requested.
- %s: The status code returned by the server (e.g., 404 for "Not Found", 500 for "Internal Server Error").
- %b: The size of the error response body in bytes.
- %{Referer}i: The Referer header, which can tell you where the request 
               originated (useful for debugging issues caused by incorrect links or bad redirects).
- %{User-Agent}i: The User-Agent header from the request, which identifies the client (browser, bot, etc.).
```

#### /var/www/ (Web Root Directory)

- The web root directory on linux systems is typically located at /var/www/. This
  directory is where the web server serves files from. This directory is used to
  serve static content. This is not required it is more by convention.

#### /usr/local/staxys/html/ (Static Content Directory for Source Installation)

- This directory holds the static files served by Staxys if installed from source.
  This is where you can store default or static content, similar to the html/ directory
  in /var/www/.

##### /usr/local/staxys/html/staxys.css:

- Default stylesheets for the Staxys interface.

##### /usr/local/staxys/html/index.html:

- The default homepage, served when accessing the root URL.

##### /usr/local/staxys/html/staxys.js:

- Default JavaScript file to provide interactivity on the homepage.

#### Global Configuration

- The staxys.conf configuration file defines the global settings for Staxys. It handles
  global configurations such as the ports to listen on, logging setup, SSL/TLS settings,
  caching, and other server-wide options. This file is essential for setting up the overall
  behavior of the Staxys service.
- Here is an example of the global configuration (staxys.conf), which should be placed
  in /etc/staxys/:

```bash
# Global Configuration for Staxys

# -------- Listen Configuration ----------

# Default ports for HTTP and HTTPS
listen_ports = "80, 443"                    

# ---- Static Content Configuration ------

# Default static content directory
server_root = "/var/www/html"     

# Default file to serve if no file is specified          
index = "index.html"         

# ------- Default Error Pages ------------
     
# Specific error pages
error_404_page = "/usr/local/staxys/html/404.html"
error_500_page = "/usr/local/staxys/html/500.html"
error_403_page = "/usr/local/staxys/html/403.html"
error_400_page = "/usr/local/staxys/html/400.html"
error_401_page = "/usr/local/staxys/html/401.html"
error_503_page = "/usr/local/staxys/html/503.html"      

# Default error page to serve when a custom error page is not defined
default_error_page = "/usr/local/staxys/html/default_error.html"        

# ---------- Log Configuration -----------

 # The path where the access logs are stored.
access_log = "/var/log/staxys/access.log"  

# The path where error logs are stored.
error_log = "/var/log/staxys/error.log" 

# Set the global log level (info, debug, error)   
log_level = "info"                          

# -------- SSL Configuration -------------

# A boolean flag to enable or disable SSL/TLS support.
ssl_enabled = true        

# Path to the SSL certificate file.                  
ssl_cert = "/etc/staxys/ssl/server.crt"    

# Path to the SSL private key file.
ssl_key = "/etc/staxys/ssl/server.key"      

# -------- Performance Configuration -------

# Number of worker processes to handle requests
worker_processes = 4               

# Max number of simultaneous connections per worker         
worker_connections = 1024                   

# Enable HTTP/2 (if supported and SSL is enabled)
http2_enabled = true                        

# Maximum allowed size for request bodies
client_max_body_size = "1m"   

 # Timeout for reading client request body              
client_body_timeout = "60s"        

# Timeout for sending responses to the client        
send_timeout = "60s"           

# Timeout for keep-alive connections
keep_alive_timeout = "75s"                 

# -------- Access Control Configuration -------

# Semicolon-separated list of allowed IPs
allow_ip = "192.168.1.1;10.0.0.0/8"         

# Semicolon-separated list of denied IPs
deny_ip = "10.0.0.0/24;192.168.2.0/24"     

# Disable basic auth by default
enable_basic_auth = false                   

# -------- Caching Configuration ---------

# Enable caching
cache_enabled = true

# Path to the cache directory                        
cache_path = "/var/cache/staxys" 

 # Cache duration in seconds           
cache_duration = "3600"                    

# -------- Health Check Configuration -------

# Enable the health check endpoint
health_check_enabled = true                

# URL for the health check endpoint 
health_check_url = "/health"                    
```

#### Server Configuration

- The server-specific configuration file (such as server1.cfg) would define the
  settings and behaviors specific to a particular service or server, such as
  routing, SSL configuration, proxy settings, and error handling.

- A server configuration file (server1.cfg) will override or extend the global
  settings with specific configurations for that server or service. This file
  will contain settings like the listening port, routes, file paths, SSL settings,
  and custom error pages.

```bash
# Server Configuration for Staxys

# The port to listen on for this server
listen = 8080                             

# The server's domain or hostname (use localhost or a specific domain name)
server_name = "example.com"

# The root directory for static content for this specific server
root = "/var/www/example.com" 

# The default index file for this server
index = "index.html"

# Enable SSL for this server (optional)
ssl_enabled = true
ssl_cert = "/etc/staxys/ssl/example.com.crt"
ssl_key = "/etc/staxys/ssl/example.com.key"

# Proxy configuration for routing to a backend service 
proxy_pass = "http://localhost:5000"  

# Custom error pages for this server
error_404_page = "/var/www/example.com/404.html"
error_500_page = "/var/www/example.com/500.html"
error_403_page = "/var/www/example.com/403.html"
error_400_page = "/var/www/example.com/400.html"
error_401_page = "/var/www/example.com/401.html"
error_503_page = "/var/www/example.com/503.html"

# Default error page for this server if no specific error page is defined
default_error_page = "/var/www/example.com/error.html"

# Specific access control for this server 
allowed_ips = "192.168.1.0/24"
denied_ips = "10.0.0.0/8"

# Enable or disable caching for this server
cache_enabled = true

# Cache duration in seconds for this server
cache_duration = "3600"  

# Logging for this specific server
access_log = "/var/log/staxys/example.com-access.log"
error_log = "/var/log/staxys/example.com-error.log"

# Can be info, debug, error
log_level = "info"  

# Timeout settings specific to this server

# Max body size for client requests
client_max_body_size = "2m"  

# Timeout for reading the request body
client_body_timeout = "60s"   

 # Timeout for sending responses to the client
send_timeout = "60s"         

# Health check endpoint 
health_check_enabled = true

# URL for the health check endpoint. This would be served 
# from the root of the server (e.g., https://example.com/health)
health_check_url = "/health"
```