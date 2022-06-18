const path = require('path');

const TEMPLATE_DIR = path.resolve(path.join(__dirname), '../../app');

const UPPERCASE_NAME_REG = /(TEMPLATE_NAME)/g;
const LOWERCASE_NAME_REG = /(template_name)/g;
const SHRINK_NAME_REG = /(templatename)/g;
const HUMP_NAME_REG = /(TemplateName)/g;
const LITTLE_HUMP_NAME_REG = /(templateName)/g;

const UNDERSCORE_LOWERCASE_NAME_REG = /(___template_name___)/g;
const UNDERSCORE_HUMP_NAME_REG = /(___TemplateName___)/g;
const UNDERSCORE_SHRINK_NAME_REG = /(___templatename___)/g;
const DASH_HUMP_NAME_REG = /(---TemplateName---)/g;
const LITTLE_DASH_HUMP_NAME_REG = /(template-name)/g;

const PERCENT_USERNAME_REG = /(%username%)/g;
const PERCENT_DATE_REG = /(%date%)/g;
const PERCENT_YEAR_REG = /(%year%)/g;
const PERCENT_HUMP_NAME_REG = /(%TemplateName%)/g;

module.exports = {
  TEMPLATE_DIR,
  UPPERCASE_NAME_REG,
  LOWERCASE_NAME_REG,
  SHRINK_NAME_REG,
  HUMP_NAME_REG,
  LITTLE_HUMP_NAME_REG,
  UNDERSCORE_LOWERCASE_NAME_REG,
  UNDERSCORE_HUMP_NAME_REG,
  UNDERSCORE_SHRINK_NAME_REG,
  DASH_HUMP_NAME_REG,
  LITTLE_DASH_HUMP_NAME_REG,
  PERCENT_USERNAME_REG,
  PERCENT_DATE_REG,
  PERCENT_YEAR_REG,
  PERCENT_HUMP_NAME_REG,
};
