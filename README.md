# GetPatched recipe: libpng1.6

GetPatched maintains target-specific backports for public distribution source packages. This repository contains the recipe, patch metadata, regression inputs, and license notices; it does not replace the distribution package with an unrelated upstream release.

## Candidate target

| Field | Value |
|---|---|
| Target | Ubuntu 20.04 LTS (Focal), amd64 |
| Pinned source | `libpng1.6` `1.6.37-2` |
| Candidate package version | `1.6.37-2+getpatched1` |
| Requested fixes | CVE-2025-65018, CVE-2026-22695, CVE-2026-22801 |
| Access | Free and public immediately after all release checks |
| Release state | Development candidate; no binary is published |

Debian and other Ubuntu targets are intentionally absent until current signed source indexes, vendor advisories, exact-source applicability, and installed-package checks establish a vulnerable target. No Ubuntu Pro or ESM source or binary is used. This repository does not claim support for arm64.

## Recipe layout

`package-manifest.json` indexes target and patch metadata. `targets/ubuntu/focal-amd64.json` pins the complete Ubuntu source package by exact version, URLs, sizes, and SHA-256 values from the signed-index preflight. `patches/metadata.json` records upstream commits, affected source versions, patch hashes, CVEs, and the required baseline and patched regressions. The source copyright file is retained under `LICENSES/`.

## Patch status

The CVE-2025-65018 candidate uses the final upstream rearchitecture (`218612d`), not the superseded preliminary depth-rejection patch. It includes the follow-up `e4f7ad4` correction for CVE-2026-22695 because that follow-up fixes an over-read introduced by the final CVE-65018 implementation. It also restores each accumulated Adam7 output row before reading later passes, addressing the pixel corruption reported in upstream issue #853. CVE-2026-22801 is tracked separately through upstream commit `cf155de`.

The recipe contains installed-image probes for CVE-2025-65018, the CVE-2026-22695 padded-stride follow-up, CVE-2026-22801 negative-stride access, and Adam7 pixel preservation. The current valid Adam7 CVE-2025-65018 probe exits cleanly on the exact Focal source baseline and candidate, so it has not reproduced that CVE and cannot support a fix claim. A corrected native ASan probe for CVE-2026-22801 reproduces a heap-buffer-overflow read on the Ubuntu-patched source and exits cleanly with the GetPatched patch; this remains source-level evidence, not an installed-package result. The Adam7 pixel comparison previously exposed corruption from the uncorrected upstream helper, motivating the row-restore correction. No target is verified or published until exact-package baseline reproduction, patched regressions, builds, fixed-database scans, and signed public APT client checks pass.

## Licensing

GetPatched-authored recipe files, patches, tests, and documentation are MIT-licensed. Upstream libpng and Ubuntu packaging retain their original licenses and notices; the MIT license does not replace those obligations. No sponsor-only access or binary license applies to this package.

## Build and verification

Use the shared `getpatched/platform` build tooling after this target is wired into its supported target and public-release workflows. A clean build must prove the vulnerable installed baseline, patched installed regressions, normal consumers, package-aware scans against a fixed database, signed repository metadata, anonymous binary installation, and source retrieval on a fresh client. The current candidate is not enabled for production publication.
