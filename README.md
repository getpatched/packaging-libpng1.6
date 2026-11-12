# GetPatched recipe: libpng1.6

GetPatched carries target-specific fixes on top of the exact Ubuntu source package. This branch isolates the Focal amd64 backport for CVE-2026-22801.

## Candidate target

| Field | Value |
|---|---|
| Target | Ubuntu 20.04 LTS (Focal), amd64 |
| Pinned source | `libpng1.6` `1.6.37-2` |
| Candidate package version | `1.6.37-2+getpatched2` |
| Included CVE | CVE-2026-22801 |
| Access | Free and public immediately after all release checks |
| Release state | Unverified development candidate; no binary is published |

## Scope and patch

This target applies only `cve-2026-22801`, upstream commit [`cf155de`](https://github.com/pnggroup/libpng/commit/cf155de014fc6c5cb199dd681dd5c8fb70429072). It prevents narrowing caller-supplied `ptrdiff_t` row strides in the simplified PNG write API. The exact installed Focal baseline reproduces an invalid read in `png_image_write_to_file` on a negative-stride write. The installed candidate must pass the same Memcheck probe.

CVE-2025-65018 and CVE-2026-22695 are not included or claimed by this isolated target; their exact baseline evidence is incomplete. The repository's retained historical fixtures and unreferenced patch file do not enter this target's recipe because `targets/ubuntu/focal-amd64.json` selects only `cve-2026-22801`.

## Recipe layout

`package-manifest.json` indexes the target and metadata. The target pins source `1.6.37-2` and its Focal source archives by the signed public source-index hashes. `patches/metadata.json` records the upstream commit, patch hash, exact target applicability, and installed baseline/patched regression expectations. Ubuntu source notices and copyright remain preserved under `LICENSES/`.

## Build and verification

Build from the pinned Focal source in a clean amd64 environment. Acceptance requires the exact installed baseline failure and candidate success, Ubuntu package tests, consumer compatibility, fixed-database package-aware before/after scans, signed isolated APT installation and source retrieval, hosted CI, independent review, and intended-branch merge. Keep production release eligibility false until every gate passes. Do not publish candidate binaries, indexes, or releases from this branch.

## Licensing

GetPatched-authored recipe files, patch, tests, and documentation are MIT-licensed. Preserve Ubuntu and upstream libpng notices and licensing. No sponsor-only access or binary license applies to this public package stream.
