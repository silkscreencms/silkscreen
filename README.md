Silkscreen CMS is a fork of the Backdrop CMS, adding the ability to use
additional database, cache, and configuration management backends to the base
Backdrop system.

Silkscreen tracks the Backdrop project in the tradition of Pressflow, and
strives to maintain as much compatibility with Backdrop as possible. Modules,
themes, and layouts created for Backdrop can be used in Silkscreen usually
without any changes.

Bugs and patches to Silkscreen can be filed at
[the issue tracker](https://github.com/silkscreencms/silkscreen-issues) on
GitHub. However, because Silkscreen tracks Backdrop, bugs and patches should
be filed with the upstream Backdrop project first whenever possible.

Silkscreen is available at
[the Silkscreen project](https://github.com/silkscreencms) on GitHub.

License
-------
Silkscreen inherits the [GPL v2](http://www.gnu.org/licenses/gpl-2.0.html)
(or higher) license from its parent.  See the LICENSE.txt file in the core
directory for complete text. Distributions of this software may relicense it as
any later version of the GPL.

The original Backdrop README.md follows:

Backdrop is a full-featured content management system that allows non-technical
users to manage a wide variety of content. It can be used to create all kinds of
websites including blogs, image galleries, social networks, intranets, and more.

Backdrop aims to provide:
- A CMS that can be used out-of-the-box.
- Code that can be learned quickly.
- Extensible APIs.

Requirements
------------
- PHP 5.3.2 or higher. Even if Backdrop can run on older versions of PHP, we
  strongly recommend that you use a
  [supported version of PHP](https://secure.php.net/supported-versions.php).
- MySQL 5.0.15 or higher with PDO enabled
- Apache (recommended) or Nginx web server
- 50 MB of disk space (recommended), 15 MB (minimum)

Installation
------------

1. Create a new database, username, and password for Backdrop to use in MySQL.

2. Point your browser at the URL of your Backdrop installation. You will be
   redirected to the install screen. If you're not redirected, visit the install
   URL. If Backdrop was installed at http://example.com/backdrop, the install
   URL would be http://example.com/backdrop/core/install.php.

3. Follow the instructions provided by the installer.

Bug Reports and Feature Requests
--------------------------------
Please use the GitHub
[issue tracker](https://github.com/backdrop/backdrop-issues/issues) for
reporting all bugs and features. We use a separate issue tracker that is not
part of the main Backdrop code repository because of GitHub's restrictions on
the use of labels and issue management.

Security Issues
---------------
If you have discovered a security issue with Backdrop CMS or any of its
[contributed modules](https://github.com/backdrop-contrib/), please contact the
Backdrop Security Team directly at
[security@backdropcms.org](mailto:security@backdropcms.org).
We manage security issues separately in a private repository until the issue has
been resolved. Even if you're not sure if it's a security problem, please
contact the security team before filing an issue.

Developers
----------
Backdrop is a fork of Drupal. It preserves the legacy audience of developers who
value ease of use and speed of learning over architectural flexibility. You can
join Backdrop's developer community by
[forking Backdrop](https://github.com/backdrop/backdrop) on GitHub.

When submitting a pull request, please make sure there is an open issue in the
[issue tracker](https://github.com/backdrop/backdrop-issues/issues) and
reference it in the description on the pull request.

Thanks to the following companies for providing sponsorship through services and
products which may be used by Backdrop contributors to build and improve the
project:

- [BrowserStack](https://www.browserstack.com) for interface testing across
  desktop and mobile browsers. *(Contact info@backdropcms.org for access
  information.)*
- [JetBrains](https://www.jetbrains.com/phpstorm/) for use of the PHPStorm IDE
  for development. *(Contact info@backdropcms.org for a license.)*
- [GitHub](https://github.com) for collaboration and code management tools.
- [ZenCI](https://zen.ci/) for continuous automated testing and sandbox testing.

User Guide
----------
Please see the the [Backdrop Handbook](https://docs.backdropcms.org/documentation/getting-started).

Developer Documentation
-----------------------
Please see the the [Backdrop API Documentation](https://docs.backdropcms.org/api/backdrop/groups).

Code of Conduct
---------------

A primary goal of the Backdrop CMS community is to be inclusive to the largest
number of contributors, with the most varied and diverse backgrounds possible.
As such, we are committed to providing a friendly, safe and welcoming
environment for all, regardless of ability, ethnicity, gender, sexual
orientation, sexual preferences, socioeconomic status, geographic location, or
religion (or lack thereof).

Our
[code of conduct](https://github.com/backdrop-ops/conduct/blob/main/code_of_conduct.md)
outlines our expectations for all those who participate in our community, as
well as the consequences for unacceptable behavior.

We invite all those who participate in the Backdrop CMS community to help us
create safe and positive experiences for everyone.

License
-------
Backdrop is [GPL v2](http://www.gnu.org/licenses/gpl-2.0.html) (or higher)
software. See the LICENSE.txt file for complete text. Distributions of this
software may relicense it as any later version of the GPL.

All Backdrop code is Copyright 2001 - 2021 by the original authors.

Backdrop also includes works under different copyright notices that are
distributed according to the terms of the GNU General Public License or a
compatible license. These individual works may have specific copyright
information noted within their source code files or directories.

