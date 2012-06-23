### Domain module

The domain module is a simple module for adding user specified domains into 
an apache2 configuration and then reload the site once in a while.

Used in conjunction with siteclone you will have a full web hosting platform,
where user can sign up for a subdomain. With the domain module the users will
be able connect any domain host with their subdomain. 

### Apache2 Conf

In your top level domain use something like this: 

    include /home/dennis/apache.conf

This will include a file were we define all our ServerAlias 

The exact placement of this file is set in domain.ini. E.g.:

    domain_apache2_serveralias_file = "/home/dennis/apache.conf"
