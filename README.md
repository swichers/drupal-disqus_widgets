This module provides comment widgets, and xautoload integration for the official
Disqus PHP library.

## Requirements

* [libraries][1]
* [xautoload][2]
* [Disqus PHP][3]

## Installation

 1. Install as usual, see http://drupal.org/node/70151 for further information.

 2. Download the Disqus PHP library from https://github.com/disqus/disqus-php and
    install into sites/all/libraries/disqus-php.

    `git clone git://github.com/disqus/disqus-php.git sites/all/libraries/disqus-php`

 3. Add the following code to the start of the disqusapi.php file after the
    initial opening php tag:

    ```php
    namespace Disqus;
    use \Exception;
    ```

 4. Configure the module at admin/config/services/disqus

## Usage

Use `disqus_widgets_disqus()` to get a Disqus API object, or use the available
blocks as designed.

See http://disqus.com/api/docs/ for API information.

[1]: https://drupal.org/project/libraries
[2]: https://drupal.org/project/xautoload
[3]: https://github.com/disqus/disqus-php
