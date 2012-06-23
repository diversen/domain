### Domain module

The domain module is a simple module for adding user specified domains into 
an apache2 configuration and then reload the site once in a while via e.g. 
a cron job

Used in conjunction with siteclone you will have a full web hosting platform,
where user can sign up for a subdomain. With the domain module the users will
be able connect any domain with their subdomain. 

e.g. you have 

    www.yoursite.com 

With siteclone a user will make a site called 

    user.yoursite.com

Then with domain module the user will be able to make a site called

    www.usersite.com

### Apache2 Conf

In your top level domain use something like this: 

    include /home/dennis/apache.conf

This will include a file were we define all our ServerAlias 

The exact placement of this file is set in domain.ini. E.g.:

    domain_apache2_serveralias_file = "/home/dennis/apache.conf"

You will need to add a system cron line that reloads apache2 once in a while. 
And you need to have a user cron job that recreates the ServerAlias File
